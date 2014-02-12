#include "processdialog.h"
#include "ui_processdialog.h"

ColorDetectController *ColorDetectController::singleton = 0;

ProcessDialog::ProcessDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProcessDialog)
{
    ui->setupUi(this);
}

ProcessDialog::~ProcessDialog()
{
    delete ui;
}

void ProcessDialog::onOpen()
{
    // Callback method of "Open" button.
    QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open Image"),
                                                        ".",
                                                        tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
    if(fileName.isEmpty()) {
        return;
    }

    // change the cursor
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // set and display the input image
    ColorDetectController::getInstance()->setInputImage(fileName.toStdString());

    cv::imshow("Input Image", ColorDetectController::getInstance()->getInputImage());

    // restore the cursor
    QApplication::restoreOverrideCursor();

}

void ProcessDialog::onProcess()
{
    // target color is hard-coded here
    ColorDetectController::getInstance()->setTargetColor(180, 90, 90);

    // process the input image and display result
    ColorDetectController::getInstance()->process();
    cv::imshow("Output Result", ColorDetectController::getInstance()->getLastResult());
}

void ProcessDialog::onClose()
{
    // Release the Singleton.
    ColorDetectController::getInstance()->destroy();
}

void ProcessDialog::on_openBtn_clicked()
{
    onOpen();
}

void ProcessDialog::on_processBtn_clicked()
{
    onProcess();
}

void ProcessDialog::on_cancleBtn_clicked()
{
    onClose();
}

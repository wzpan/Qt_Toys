#include "mainwindow.h"
#include "ui_mainwindow.h"

ColorDetectController *ColorDetectController::singleton = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    onClose();
}


void MainWindow::on_openBtn_clicked()
{
    onOpen();
}


void MainWindow::on_processBtn_clicked()
{
    onProcess();
}

void MainWindow::on_colorBtn_clicked()
{
    onSelectColor();
}

void MainWindow::on_thresholdSlider_sliderReleased()
{
    onSelectThreshold();
}

void MainWindow::on_thresholdSlider_valueChanged(int value)
{
    ui->thresholdLabel->setText(tr("Color Distance Threshold: %1")
                                .arg(value));
}

void MainWindow::on_saveBtn_clicked()
{
    onSave();
}

/** 
 * showImage	-	display an image on label
 *
 * @param image	-	image for displaying
 */
void MainWindow::showImage(cv::Mat image)
{
    cv::Mat tmp;
    QImage img;
    if (image.channels() == 3) {    // color image
        cv::cvtColor(image, tmp, CV_BGR2RGB);
        img = QImage((const unsigned char*)(tmp.data),
                        tmp.cols, tmp.rows, QImage::Format_RGB888);
    } else if (image.channels() == 1) {     // gray scale image
        cv::cvtColor(image, tmp, CV_GRAY2RGB);
        img = QImage((const unsigned char*)(tmp.data),
                        tmp.cols, tmp.rows, QImage::Format_RGB888);
    }
    // display on label
    ui->imageLabel->setPixmap(QPixmap::fromImage(img));
    ui->imageLabel->repaint();
}

/** 
 * onOpen()	-	open image
 *
 */
void MainWindow::onOpen()
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

    showImage(ColorDetectController::getInstance()->getInputImage());

    // restore the cursor
    QApplication::restoreOverrideCursor();

    // get the file's standard location
    curFile = QFileInfo(fileName).canonicalPath();

    ui->processBtn->setEnabled(true);
    ui->thresholdSlider->setEnabled(true);
    ui->colorBtn->setEnabled(true);
    ui->saveBtn->setEnabled(true);
}

/** 
 * onSelectColor()	-	select target color
 *
 */
void MainWindow::onSelectColor()
{
    QColor color = QColorDialog::getColor(Qt::green, this);
    if (color.isValid()) {
        ColorDetectController::getInstance()
                ->setTargetColor(color.red(),color.green(),color.blue());
    }
}

/** 
 * onSelectThreshold	-	select threshold
 *
 */
void MainWindow::onSelectThreshold()
{
    ColorDetectController::getInstance()
            ->setColorDistanceThreshold(
                ui->thresholdSlider->value());
}

/**
 * saveImage	-	Save the file to a specified location
 *
 * @param fileName	-	the target location
 *
 * @return true if the file is successfully saved
 */
bool MainWindow::saveImage(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly)) {
        QMessageBox::warning(this, tr("ImageViewer"),
                             tr("Enable to save %1: \n %2")
                             .arg(fileName).arg(file.errorString()));
        return false;
    }

    // change the cursor
    QApplication::setOverrideCursor(Qt::WaitCursor);

    // save all the contents to file
    cv::imwrite(fileName.toStdString(), ColorDetectController::getInstance()->getLastResult());

    // restore the cursor
    QApplication::restoreOverrideCursor();

    return true;
}

/** 
 * onProcess	-	process image
 *
 */
void MainWindow::onProcess()
{
    ColorDetectController::getInstance()->process();
    cv::Mat resulting =
            ColorDetectController::getInstance()->getLastResult();
    if (!resulting.empty())
        showImage(resulting);
}

/** 
 * onSave	-	save the image
 *
 */
void MainWindow::onSave()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save as"),
                                                    curFile);
    if (!fileName.isEmpty())
        saveImage(fileName);
}

/** 
 * onClose	-	destroy the instance
 *
 */
void MainWindow::onClose()
{
    ColorDetectController::getInstance()->destroy();
}

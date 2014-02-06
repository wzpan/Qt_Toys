#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    updateStatus(false);

    // basic image processor
    processor = 0;

    // morphology dialog
    morphoDialog = 0;    
    // morphology processor
    morphoProcessor = 0;

    isModified = false;

    emptyTip = "Please open an image.";
    ui->imageLabel->setText(emptyTip);

    // Set timer by 1 sec
    timer = startTimer(1000);

    // Status bar
    timeLabel = new QLabel;
    ui->statusBar->addPermanentWidget(timeLabel);
}

MainWindow::~MainWindow()
{
    delete ui;
}


/** 
 * updateStatus	-	Update the enable property of the edit menu
 *
 * @param vi	-	the enable variable
 */
void MainWindow::updateStatus(bool vi)
{    
    for (int i = 0; i < ui->menuEdit->actions().count(); ++i){
        ui->menuEdit->actions().at(i)->setEnabled(vi);
    }
    ui->actionClose->setEnabled(vi);
    ui->actionSave->setEnabled(vi);
    ui->actionSave_as->setEnabled(vi);
}

void MainWindow::setProcessor(ImageProcessor *imgProcessorPtr)
{
    // this is the frame processor instance that will be called
    processor = imgProcessorPtr;
}

/** 
 * closeEvent	-	Do a file save check before close the application
 *
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}


/**
 * timerEvent	-	Update the time label
 *
 */
void MainWindow::timerEvent(QTimerEvent *)
{
    timeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm::ss"));
}

/** 
 * maybeSave	-	some thing to do before the next operation
 *
 * @return true if all preparation has done; false if the user cancel the operation.
 */
bool MainWindow::maybeSave()
{
    if (isModified){
        // Create an warning dialog
        QMessageBox box;
        box.setWindowTitle(tr("Warning"));
        box.setIcon(QMessageBox::Warning);
        box.setText(tr("The current file %1 has been changed. Save?").arg(curFile));

        QPushButton *yesBtn = box.addButton(tr("Yes(&Y)"),
                                            QMessageBox::YesRole);
        box.addButton(tr("No(&N)"), QMessageBox::NoRole);
        QPushButton *cancelBut = box.addButton(tr("Cancel(&C)"),
                                           QMessageBox::RejectRole);

        box.exec();
        if (box.clickedButton() == yesBtn)
            return save();
        if (box.clickedButton() == cancelBut)
            return false;
    }
    return true;
}

/** 
 * save	-	Save the file
 *
 * @return true if the file is successfully saved
 */
bool MainWindow::save()
{
    return saveImage(curFile);
}


/** 
 * saveAs	-	Save the file as...
 *
 *
 * @return true if the file is successfully saved to the
 * 			user defined location
 */
bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save as"),
                                                    curFile);

    if (fileName.isEmpty()) return false;
    return saveImage(fileName);
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
    QString target;
    if (QFileInfo(fileName).suffix() == "")
        target = fileName + ".png";
    QFile file(target);

    if (!file.open(QFile::WriteOnly)) {
        QMessageBox::warning(this, tr("ImageViewer"),
                             tr("Enable to save %1: \n %2")
                             .arg(target).arg(file.errorString()));
        return false;
    }

    // change the cursor
    QApplication::setOverrideCursor(Qt::WaitCursor);
    
    // save all the contents to file
    imwrite(target.toStdString(), src);
        
    // restore the cursor
    QApplication::restoreOverrideCursor();

    // get the file's standard location
    curFile = QFileInfo(target).canonicalPath();
    setWindowTitle(curFile);

    isModified = false;

    return true;
}


/** 
 * loadImage	-	Open and load a specified file
 *
 * @param fileName	-	file location
 *
 * @return true if the file is successfully loaded
 */
bool MainWindow::loadImage(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(this, tr("ImageViewer"),
                             tr("Unable to load file %1:\n%2.")
                             .arg(fileName).arg(file.errorString()));
        return false;
    }

    // change the cursor
    QApplication::setOverrideCursor(Qt::WaitCursor);
    
    // Load all the contents to the label
    src = imread(fileName.toStdString());
    temp = src.clone();

    // Display image
    showImage(temp);
    
    // restore the cursor
    QApplication::restoreOverrideCursor();

    // set the current file location
    curFile = QFileInfo(fileName).canonicalPath();
    setWindowTitle(curFile);
    isModified = false;
    return true;
}

void MainWindow::showImage(Mat image)
{
    Mat tmp;
    cvtColor(image, tmp, CV_BGR2RGB);
    QImage img = QImage((const unsigned char*)(tmp.data),
                        tmp.cols, tmp.rows, QImage::Format_RGB888);

    ui->imageLabel->setPixmap(QPixmap::fromImage(img));
    ui->imageLabel->repaint();
}

// Open image file
void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"),
                                                    ".",
                                                    tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
    if(!fileName.isEmpty()) {
        loadImage(fileName);
        updateStatus(true);
    }
}

// Quit
void MainWindow::on_actionQuit_triggered()
{
    // Execute the close operation before quit.
    on_actionClose_triggered();

    qApp->quit();
}

// Close image
void MainWindow::on_actionClose_triggered()
{
    if (maybeSave()) {
        updateStatus(false);
        ui->imageLabel->setText(emptyTip);
        isModified = false;
    }
}

// Save As operation
void MainWindow::on_actionSave_as_triggered()
{
    saveAs();
}

// Save operation
void MainWindow::on_actionSave_triggered()
{
    save();
}


/** 
 * about	-	display about info
 *
 */
void MainWindow::about()
{
    QMessageBox::about(this, tr("About ImageViewer"),
                       tr("<h2>ImageViewer 1.0</h2>"
                          "<p>Copyright &copy; 2013 Software Inc.</p>"
                          "<p>ImageViewer is a small application to "
                          "view and adjust images.</p>"));
}

// About
void MainWindow::on_actionAbout_triggered()
{
    about();
}

// About Qt
void MainWindow::on_actionAbout_Qt_triggered()
{
    qApp->aboutQt();
}

// Morphology dialog
void MainWindow::on_actionMorpho_triggered()
{
    if (!morphoProcessor)
        morphoProcessor = new MorphoProcessor();

    // set morphology processor as the current frame processor
    setProcessor(morphoProcessor);

    if (!morphoDialog) {
        morphoDialog = new MorphoDialog(this, morphoProcessor);

        connect(morphoDialog, SIGNAL(preview()),
                this, SLOT(preview())
                );

        connect(morphoDialog, SIGNAL(reset()),
                this, SLOT(reset())
                );
    }

    morphoDialog->show();
    morphoDialog->raise();
    morphoDialog->activateWindow();

    if (morphoDialog->exec() == QDialog::Accepted) {
        process();
    } else {
        reset();
    }
}

/** 
 * preview	-	preview the processing result
 *
 */
void MainWindow::preview()
{
    processor->process(src, temp);

    showImage(temp);
}

/** 
 * process	-	process the image
 * 
 * Process the image by using the current processor.
 * Be sure to select a processor by using setProcessor()
 *
 */
void MainWindow::process()
{
    processor->process(src, temp);
    src = temp.clone();
    showImage(temp);
    isModified = true;
}

/** 
 * reset	-	cancel the processing and reset the image
 *
 */
void MainWindow::reset()
{
    temp = src.clone();
    showImage(temp);
}

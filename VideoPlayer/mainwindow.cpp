#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    rateLabel = new QLabel;         // Frame rate

    isModified = false;
    isPlay = false;

    updateStatus(false);
    updateBtn();

    emptyTip = "Please open a video.";
    ui->imageLabel->setText(emptyTip);

    // Status bar    
    rateLabel->setText("");
    ui->statusBar->addPermanentWidget(rateLabel);
}

MainWindow::~MainWindow()
{
    delete ui;
}


/** 
 * updateEnable	-	Update the enabled property of play menu and filter menu
 *
 * @param vi	-	the enable variable
 */
void MainWindow::updateStatus(bool vi)
{    
    for (int i = 0; i < ui->menuPlay->actions().count(); ++i){        
        ui->menuPlay->actions().at(i)->setEnabled(vi);
    }
    for (int i = 0; i < ui->menuFilter->actions().count(); ++i){
        ui->menuFilter->actions().at(i)->setEnabled(vi);
    }
    ui->actionClose->setEnabled(vi);
    ui->actionSave->setEnabled(vi);
    ui->actionSave_as->setEnabled(vi);
    ui->progressSlider->setEnabled(vi);
    ui->btnLast->setEnabled(vi);;
    ui->btnNext->setEnabled(vi);
    ui->btnPlay->setEnabled(vi);
    ui->btnStop->setEnabled(vi);

    if(!vi){
        ui->progressSlider->setValue(0);
        rateLabel->setText("");
    }
}

/** 
 * updateBtn	-	swith the visibility of play/pause button
 *
 * swith the visibility of play/pause button according to the current status
 */
void MainWindow::updateBtn()
{
    ui->actionPause->setVisible(isPlay);
    ui->btnPause->setVisible(isPlay);
    ui->actionPlay->setVisible(!isPlay);
    ui->btnPlay->setVisible(!isPlay);
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
    return saveFile(curFile);
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
    return saveFile(fileName);
}


/** 
 * saveFile	-	Save the file to a specified location
 *
 * @param fileName	-	the target location
 *
 * @return true if the file is successfully saved
 */
bool MainWindow::saveFile(const QString &fileName)
{
    QString target;
    if (QFileInfo(fileName).suffix() == "")
        target = fileName + ".avi";
    QFile file(target);

    if (!file.open(QFile::WriteOnly)) {
        QMessageBox::warning(this, tr("VideoPlayer"),
                             tr("Enable to save %1: \n %2")
                             .arg(target).arg(file.errorString()));
        return false;
    }

    // change the cursor
    QApplication::setOverrideCursor(Qt::WaitCursor);
    
    // save all the contents to file

    // ***********************************
    // todo
    // ************************************
        
    // restore the cursor
    QApplication::restoreOverrideCursor();

    // get the file's standard location
    curFile = QFileInfo(target).canonicalPath();
    setWindowTitle(curFile);

    isModified = false;

    return true;
}


/** 
 * loadFile	-	Open and load a video
 *
 * @param fileName	-	file location
 *
 * @return true if the file is successfully loaded
 */
bool MainWindow::LoadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(this, tr("VideoPlayer"),
                             tr("Unable to load file %1:\n%2.")
                             .arg(fileName).arg(file.errorString()));
        return false;
    }

    // change the cursor
    QApplication::setOverrideCursor(Qt::WaitCursor);
    
    // open the video file
    capture.open(fileName.toStdString());

    // check if video successfully opened
    if (!capture.isOpened())
        return false;

    // get the frame rate
    rate = capture.get(CV_CAP_PROP_FPS);
    delay = 1000/rate;
    rateLabel->setText(tr("rate: %1").arg(rate));

    // initialize the playing status
    if (!revert())
        return false;

    // restore the cursor
    QApplication::restoreOverrideCursor();

    // set the current file location
    curFile = QFileInfo(fileName).canonicalPath();
    setWindowTitle(curFile);
    isModified = false;
    isPlay = false;
    return true;
}


/** 
 * showImage	-	show a image
 *
 * @param image	-	the image to be showed
 *
 * Mainly used for display a single frame
 */
void MainWindow::showImage(Mat image)
{
    Mat tmp;
    cvtColor(image, tmp, CV_BGR2RGB);
    QImage img = QImage((const unsigned char*)(tmp.data),
                        tmp.cols, tmp.rows, QImage::Format_RGB888);

    ui->imageLabel->setPixmap(QPixmap::fromImage(img));
    ui->imageLabel->repaint();
}

/** 
 * play	-	play the video
 *
 */
void MainWindow::play()
{
    bool isEnd = false;
    isPlay = true;
    updateBtn();
    while (!isEnd){
        // read next frame if any
        if (!capture.read(frame)){
            isEnd = true;
            break;
        }
        showImage(frame);
        curPos = capture.get(CV_CAP_PROP_POS_FRAMES);
        ui->progressSlider->setValue(curPos * 100 / length);
        sleep(delay);
        if (isPlay == false)
            break;
    }
    if (isEnd)
        revert();
}


/** 
 * pause	-	pause playing
 *
 */
void MainWindow::pause()
{
    isPlay = false;
    updateBtn();
}

/** 
 * revert	-	revert progress
 *
 * Used for reset the UI when Load/Stop video
 */
bool MainWindow::revert()
{
    updateBtn();
    ui->progressSlider->setValue(0);

    // goto the first frame
    capture.set(CV_CAP_PROP_POS_FRAMES, 0.0);

    // get the progress info
    length = capture.get(CV_CAP_PROP_FRAME_COUNT);
    curPos = 0;

    // display the first frame
    if (!capture.read(frame)){
        QMessageBox::warning(this, tr("VideoPlayer"),
                             tr("The video has no frames!")
                             );
        return false;
    } else {
        showImage(frame);
    }
    return true;
}


/** 
 * stop	-	stop playing
 *
 */
void MainWindow::stop()
{
    pause();
    revert();
}

/** 
 * jumpTo	-	jump to a specified position
 *
 * @param index	-	the frame index
 */
void MainWindow::jumpTo(long index)
{
    // goto the corresponding frame
    capture.set(CV_CAP_PROP_POS_FRAMES, index);
    
    if(!isPlay){
        capture.read(frame);
        showImage(frame);
    }
}

/** 
 * preFrame	-	go to the previous frame
 *
 */
void MainWindow::preFrame()
{
    if(isPlay)
        pause();
    if (curPos >= 0){
        curPos -= 1;
        jumpTo(curPos);
    }
}

/** 
 * nextFrame	-	go to the next frame
 *
 */
void MainWindow::nextFrame()
{
    if(isPlay)
        pause();
    curPos += 1;
    if (curPos <= length){
        jumpTo(curPos);
    }
}

void MainWindow::process()
{
    // ***********************************
    // todo
    // ************************************
}

/** 
 * sleep	-	pause the current thread for some milliseconds
 *
 * @param msecs	-	number of milliseconds to pause
 *
 * Mainly used for delay the video so as to keep the frame ratio
 */
void MainWindow::sleep(int msecs)
{
    QTime dieTime= QTime::currentTime().addMSecs(msecs);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

/** 
 * about	-	Display about info
 *
 */
void MainWindow::about()
{
    QMessageBox::about(this, tr("About VideoPlayer"),
                       tr("<h2>VideoPlayer 1.0</h2>"
                          "<p>Copyright &copy; 2013 Software Inc.</p>"
                          "<p>VideoPlayer is a small application to "
                          "play and process videos.</p>"));
}



// Open video file
void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Video"),
                                                    ".",
                                                    tr("Video Files (*.avi *.mov *.mpeg)"));
    if(!fileName.isEmpty()) {
        if(LoadFile(fileName))
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

// Close video
void MainWindow::on_actionClose_triggered()
{
    if (maybeSave()) {
        capture.release();
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

void MainWindow::on_btnPlay_clicked()
{
    play();
}


void MainWindow::on_actionStop_S_triggered()
{
    stop();
}
void MainWindow::on_btnStop_clicked()
{
    stop();
}

void MainWindow::on_actionPlay_triggered()
{
    play();
}

void MainWindow::on_actionPause_triggered()
{
    pause();
}

void MainWindow::on_btnPause_clicked()
{
    pause();
}

void MainWindow::on_btnNext_clicked()
{
    nextFrame();
}

void MainWindow::on_progressSlider_valueChanged(int value)
{
    curPos = value * length / 100;
    jumpTo(curPos);
}

void MainWindow::on_btnLast_clicked()
{
    preFrame();
}

void MainWindow::on_actionProcess_triggered()
{
    process();
}

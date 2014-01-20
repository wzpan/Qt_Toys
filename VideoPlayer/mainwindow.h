#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QDateTime>
#include <QFileDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void updateStatus(bool vi);   // Update objects' ability
    void updateBtn();             // Update button's visibility

    // File functions
	bool maybeSave();   // whether needs save
    bool save();        // save
    bool saveAs();      // save as
    bool saveFile(const QString &fileName);     // save file
    bool LoadFile(const QString &fileName);    // load file
    void showImage(Mat img);        // display image on label control

    // Play functions
    void play();        // play video
    void pause();       // pause playing
    bool revert();      // revert progress
    void stop();        // stop playing
    void jumpTo (long pos);   // jump to a position
    void preFrame();   // pause and display previous frame
    void nextFrame();   // pause and display next frame

    // Process Video
    void process();

    void sleep(int msecs);

    // Help functions
    void about();
    void aboutQt();

private slots:
    void on_actionOpen_triggered();

    void on_actionQuit_triggered();

    void on_actionClose_triggered();

    void on_actionSave_as_triggered();

    void on_actionSave_triggered();

    void on_actionAbout_triggered();

    void on_actionAbout_Qt_triggered();

    void on_actionStop_S_triggered();

    void on_btnPlay_clicked();

    void on_btnStop_clicked();

    void on_actionPlay_triggered();

    void on_actionPause_triggered();

    void on_btnPause_clicked();

    void on_btnNext_clicked();

    void on_progressSlider_valueChanged(int value);

    void on_btnLast_clicked();

    void on_actionProcess_triggered();

protected:
    void closeEvent(QCloseEvent *event);    // Close event
    
private:
    Ui::MainWindow *ui;
    QString emptyTip;   // tips when no image is opened

    bool isModified;   // whether the file has been modified
    bool isPlay;        // whether is playing

    QLabel *rateLabel;     // frame label

    QString curFile;        // current file's location

    QIcon iconPlay;
    QIcon iconPause;

    VideoCapture capture;   // video sequence
    Mat frame;              // current video frame
    double rate;            // video frame rate
    int delay;              // delay between each frame in ms
    long length;          // length of the video
    long curPos;           // the current progress
    QDateTime wholeTime;      // the whole lasting time of the video
    QDateTime curTime;         // the current time
};

#endif // MAINWINDOW_H

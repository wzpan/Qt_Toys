#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QDateTime>
#include <QFileDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <queue>
#include <dbg.h>
#include "VideoProcessor.h"
#include "ErosionProcessor.h"
#include "WindowHelper.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class VideoProcessor;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();    

    // File functions
	bool maybeSave();   // whether needs save
    bool save();        // save
    void play();        // save
    bool saveAs();      // save as
    bool saveFile(const QString &fileName);     // save file
    bool LoadFile(const QString &fileName);    // load file

    // Help functions
    void about();
    void aboutQt();

private slots:
    void on_actionOpen_triggered();

    void on_actionQuit_triggered();

    void on_actionClose_triggered();

    void on_actionSave_as_triggered();

    void on_actionAbout_triggered();

    void on_actionAbout_Qt_triggered();

    void on_actionStop_S_triggered();

    void on_btnPlay_clicked();

    void on_btnStop_clicked();

    void on_actionPlay_triggered();

    void on_actionPause_triggered();

    void on_btnPause_clicked();

    void on_btnNext_clicked();

    void on_btnLast_clicked();  

    void showFrame(cv::Mat frame);    

    void on_action_Erosion_triggered();

    void revert();

    void sleep(int msecs);

    void updateBtn();

    void updateProgressBar();

    void on_progressSlider_sliderMoved(int position);

protected:
    void closeEvent(QCloseEvent *);
    
private:
    Ui::MainWindow *ui;    

    void updateStatus(bool vi);

    // tips when no image is opened
    QString inputTip;
    QString outputTip;

    // frame label
    QLabel *rateLabel;
    // current file's location
    QString curFile;

    // video processor instance
    VideoProcessor *video;

    WindowHelper *helper;

    void clean();
};

#endif // MAINWINDOW_H

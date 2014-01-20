#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QDateTime>
#include <QFileDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include "adjustdialog.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace Ui {
    class MainWindow;
}

using namespace cv;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void updateStatus(bool vi);   // Update objects' visibility

    // File functions
	bool maybeSave();   // whether needs save
    bool save();        // save
    bool saveAs();      // save as
    bool saveImage(const QString &fileName);     // save file
    bool loadImage(const QString &fileName);    // load file
    void showImage(Mat img);        // display image on label control

    void erosion();
    void dilation();
    void adjust();

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
    void on_actionAdjust_triggered();
    void reset();
    void preview();

protected:
    void closeEvent(QCloseEvent *event);    // Close event
    void timerEvent(QTimerEvent *);         // Timer event
    
private:
    Ui::MainWindow *ui;

    QString emptyTip;   // tips when no image is opened
    bool isModified;   // whether the file has been modified
    QString curFile;	// current file's location
    cv::Mat image, src, temp;			// the image variable

    int type;       // adjust type. 0: erosion; 1: dilation
    int elem;       // element type. 0: rect; 1. cross; 2. ellipse
    int size;       // kernel size

    // adjust dialog
    AdjustDialog *adjustDialog;

    int timer;			// timer
    QLabel *timeLabel;	// time label
};

#endif // MAINWINDOW_H

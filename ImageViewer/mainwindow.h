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

    void updateStates(bool vi);   // Update objects' visibility

    // File functions
	bool maybeSave();   // whether needs save
    bool save();        // save
    bool saveAs();      // save as
    bool saveImage(const QString &fileName);     // save file
    bool loadImage(const QString &fileName);    // load file

    void Erosion( int, void* );
    void Dilation( int, void* );

    // Help functions
    void about();
    void aboutQt();

private slots:
    void on_actionOpen_triggered();

    void on_actionQuit_triggered();

    void on_actionClose_triggered();

    void on_actionSave_as_triggered();

    void on_actionSave_triggered();

protected:
    void closeEvent(QCloseEvent *event);    // Close event
    void timerEvent(QTimerEvent *);         // Timer event
    
private:
    Ui::MainWindow *ui;

    QString emptyTip;   // tips when no image is opened
    bool isModified;   // whether the file has been modified
    QString curFile;	// current file's location
    Mat image;			// the image variable
    int timer;			// timer
    QLabel *timeLabel;	// time label
};

#endif // MAINWINDOW_H

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
#include "ImageProcessor.h"
#include "MorphoDialog.h"
#include "MorphoProcessor.h"
#include "SaltDialog.h"
#include "SaltProcessor.h"

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

    // File functions
	bool maybeSave();   // whether needs save
    bool save();        // save
    bool saveAs();      // save as
    bool saveImage(const QString &fileName);     // save file
    bool loadImage(const QString &fileName);    // load file
    void showImage(Mat img);        // display image

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

    void on_actionMorpho_triggered();

    void preview();		// preview image

    void reset();    	// cancel processing

    void on_actionSalt_Pepper_Noise_triggered();

protected:
    void closeEvent(QCloseEvent *event);    // Close event
    
private:
    void updateStatus(bool vi);   // Update objects' visibility
    void setProcessor(ImageProcessor *imgProcessorPtr);		// Set current processor 
    void process();  // Process image

    Ui::MainWindow *ui;

    QString emptyTip;   // tips when no image is opened
    bool isModified;   // whether the file has been modified
    QString curFile;	// current file's location
    cv::Mat image, src, temp;			// the image variable

    // Processor basic class
    ImageProcessor *processor;

    // morphology
    MorphoDialog *morphoDialog;
    MorphoProcessor *morphoProcessor;

    // salt-and-pepper noise
    SaltDialog *saltDialog;
    SaltProcessor *saltProcessor;

    QLabel *sizeLabel;	// size label
};

#endif // MAINWINDOW_H

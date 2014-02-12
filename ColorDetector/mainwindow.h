#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include "ColorDetector.h"
#include "ColorDetectController.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *);

private slots:

    void on_openBtn_clicked();

    void on_processBtn_clicked();

    void on_colorBtn_clicked();

    void on_thresholdSlider_sliderReleased();

    void on_saveBtn_clicked();

    void on_thresholdSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    QString curFile;	// current file's location

    // save image to file
    bool saveImage(const QString &fileName);
    // show image
    void showImage(cv::Mat image);

    // open image
    void onOpen();
    // select color
    void onSelectColor();
    // select threshold
    void onSelectThreshold();
    // process image
    void onProcess();
    // save image
    void onSave();
    // close window
    void onClose();
};

#endif // MAINWINDOW_H

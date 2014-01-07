#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>
#include <QDateTime>
#include <QLabel>
#include "finddialog.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void updateEnable(bool vi);   // Update objects' visibility

    // File functions
    void newFile();     // New file
    bool maybeSave();   // whether needs save
    bool save();        // save
    bool saveAs();      // save as
    bool saveFile(const QString &fileName);     // save file
    bool loadFile(const QString &fileName);    // load file

    // Help functions
    void about();
    void aboutQt();

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionClose_triggered();
    void on_actionQuit_triggered();
    void on_actionCancel_triggered();
    void on_actionCut_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionFind_triggered();
    void on_actionAbout_Qt_triggered();
    void on_actionAbout_triggered();
    void on_actionSelect_All_triggered();
    void on_actionRedo_triggered();
    void find(const QString &str, QTextDocument::FindFlags flag);

protected:
    void closeEvent(QCloseEvent *event);    // Close event
    void timerEvent(QTimerEvent *);         // Timer event

private:
    Ui::MainWindow *ui;

    int timer;             // timer

    // variables
    bool isUntitled;	// True: haven't bee saved. False: Otherwise
    QString curFile;	// Current file's location
    
    // find dialog
    FindDialog *findDialog;

    // time label
    QLabel *timeLabel;
};

#endif // MAINWINDOW_H




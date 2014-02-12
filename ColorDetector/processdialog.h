#ifndef PROCESSDIALOG_H
#define PROCESSDIALOG_H

#include <QDialog>
#include <QFileDialog>

#include "ColorDetector.h"
#include "ColorDetectController.h"

namespace Ui {
class ProcessDialog;
}

class ProcessDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProcessDialog(QWidget *parent = 0);
    ~ProcessDialog();

private slots:
    void on_openBtn_clicked();

    void on_processBtn_clicked();

    void on_cancleBtn_clicked();


private:
    Ui::ProcessDialog *ui;

    void onOpen();
    void onProcess();
    void onClose();
};

#endif // PROCESSDIALOG_H

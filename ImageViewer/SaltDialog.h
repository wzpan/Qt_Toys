#ifndef SALTDIALOG_H
#define SALTDIALOG_H

#include <QDialog>
#include "SaltProcessor.h"

namespace Ui {
class SaltDialog;
}

class SaltDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaltDialog(QWidget *parent = 0,
                        SaltProcessor *processor = 0);
    ~SaltDialog();

protected:
    void showEvent(QShowEvent *);

private slots:
    void on_checkPreview_toggled(bool checked);

    void on_numSlider_valueChanged(int value);

signals:
    void preview(); // preview image in real-time
    void reset();   // reset image

private:
    Ui::SaltDialog *ui;
    SaltProcessor *processor;

    bool showPreview;
};

#endif // SALTDIALOG_H

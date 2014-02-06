#ifndef EROSIONDIALOG_H
#define EROSIONDIALOG_H

#include <QDialog>
#include "ErosionProcessor.h"

namespace Ui {
class ErosionDialog;
}

class ErosionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ErosionDialog(QWidget *parent = 0,
                           ErosionProcessor *processor = 0);
    ~ErosionDialog();
    int getSize();
    int getElem();
    void setSize(int);
    void setElem(int);
    void setParam(int, int);

private slots:
    void on_comboElement_currentIndexChanged(int index);
    void on_sizeSlider_valueChanged(int value);

signals:
    void process();

private:
    Ui::ErosionDialog *ui;
    ErosionProcessor *processor;
};

#endif // EROSIONDIALOG_H

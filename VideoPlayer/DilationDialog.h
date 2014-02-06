#ifndef DILATIONDIALOG_H
#define DILATIONDIALOG_H

#include <QDialog>
#include <DilationProcessor.h>

namespace Ui {
class DilationDialog;
}

class DilationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DilationDialog(QWidget *parent = 0, DilationProcessor *processor = 0);
    ~DilationDialog();

private slots:
    void on_sizeSlider_valueChanged(int value);

    void on_comboElement_currentIndexChanged(int index);

private:
    Ui::DilationDialog *ui;
    DilationProcessor *processor;
};

#endif // DILATIONDIALOG_H

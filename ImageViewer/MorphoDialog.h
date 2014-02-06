#ifndef MORPHODIALOG_H
#define MORPHODIALOG_H

#include <QDialog>
#include "MorphoProcessor.h"

namespace Ui {
class MorphoDialog;
}

class MorphoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MorphoDialog(QWidget *parent = 0,
                          MorphoProcessor *processor = 0);
    ~MorphoDialog();

protected:
    void showEvent(QShowEvent *);

signals:
    void preview(); // preview image in real-time
    void reset();   // reset image

private slots:
    void on_comboType_currentIndexChanged(int index);
    void on_comboElement_currentIndexChanged(int index);
    void on_sizeSlider_valueChanged(int value);
    void on_checkPreview_clicked();

private:
    Ui::MorphoDialog *ui;
    MorphoProcessor *processor;

    bool showPreview;
};

#endif // MORPHODIALOG_H

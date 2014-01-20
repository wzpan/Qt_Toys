#ifndef ADJUSTDIALOG_H
#define ADJUSTDIALOG_H

#include <QDialog>

namespace Ui {
class AdjustDialog;
}

class AdjustDialog : public QDialog
{
    Q_OBJECT

    friend class MainWindow;

public:
    explicit AdjustDialog(QWidget *parent = 0);
    ~AdjustDialog();

signals:
    void preview(); // preview image in real-time
    void reset();   // reset image

private slots:
    void on_comboType_currentIndexChanged(int index);
    void on_comboElement_currentIndexChanged(int index);
    void on_sizeSlider_valueChanged(int value);

    void on_checkPreview_clicked();

private:
    Ui::AdjustDialog *ui;

    bool showPreview;

    int type;
    int elem;
    int size;
};

#endif // ADJUSTDIALOG_H

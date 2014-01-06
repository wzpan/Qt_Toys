#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QTextDocument>
#include <stdio.h>

namespace Ui {
class FindDialog;
}

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = 0);
    ~FindDialog();

signals:
    void find(const QString &str, QTextDocument::FindFlags flag);

private slots:
    void findClicked();
    void on_findButton_clicked();
    void on_closeButton_clicked();
    void on_lineEdit_textChanged(const QString &text);

private:
    Ui::FindDialog *ui;
};

#endif // FINDDIALOG_H

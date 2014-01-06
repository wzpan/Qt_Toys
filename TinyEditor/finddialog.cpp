#include "finddialog.h"
#include "ui_finddialog.h"

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);
    ui->findButton->setEnabled(false);
}

FindDialog::~FindDialog()
{
    delete ui;
}

void FindDialog::findClicked()
{
    QString text = ui->lineEdit->text();
    QTextDocument::FindFlags flag = 0;

    if (ui->backwardCheckBox->isChecked()) {
        flag |= QTextDocument::FindBackward;
    }

    if (ui->caseCheckBox->isChecked()) {
        flag |= QTextDocument::FindCaseSensitively;
    }

    // emit the "find" signal
    emit find(text, flag);
}


void FindDialog::on_findButton_clicked()
{
    findClicked();
}

void FindDialog::on_closeButton_clicked()
{
    this->close();
}

void FindDialog::on_lineEdit_textChanged(const QString &text)
{
    ui->findButton->setEnabled(!text.isEmpty());
}

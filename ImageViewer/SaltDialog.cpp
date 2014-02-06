#include "SaltDialog.h"
#include "ui_SaltDialog.h"

SaltDialog::SaltDialog(QWidget *parent, SaltProcessor *processor) :
    QDialog(parent),
    ui(new Ui::SaltDialog)
{
    ui->setupUi(this);
    this->processor = processor;

    showPreview = true;

    ui->numSlider->setValue(processor->num);
    ui->checkPreview->setChecked(showPreview);
    ui->numLabel->setText(tr("<p>Particle Num:</p>"
                              "<p><b>%1</b></p>").arg(processor->num));
}

SaltDialog::~SaltDialog()
{
    delete ui;
}

void SaltDialog::showEvent(QShowEvent *)
{
    if (showPreview)
        emit preview();
}

void SaltDialog::on_checkPreview_toggled(bool checked)
{
    showPreview = checked;
    if (showPreview)
        emit preview();
    else
        emit reset();
}

void SaltDialog::on_numSlider_valueChanged(int value)
{
    processor->num = value;

    ui->numLabel->setText(tr("<p>Particle Num:</p>"
                              "<p><b>%1</b></p>").arg(processor->num));

    if (showPreview)
        emit preview();
}

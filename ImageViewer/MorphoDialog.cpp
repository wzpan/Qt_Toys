#include "MorphoDialog.h"
#include "ui_MorphoDialog.h"

MorphoDialog::MorphoDialog(QWidget *parent, MorphoProcessor *processor) :
    QDialog(parent),
    ui(new Ui::MorphoDialog)
{
    this->processor = processor;
    ui->setupUi(this);

    showPreview = true;

    ui->comboType->setCurrentIndex(processor->type);
    ui->comboElement->setCurrentIndex(processor->elem);
    ui->sizeSlider->setValue(processor->size);
    ui->checkPreview->setChecked(showPreview);

    ui->sizeLabel->setText(tr("<p>Kernel Size:</p>"
                              "<p><b>%1</b></p>").arg(processor->size));

}

MorphoDialog::~MorphoDialog()
{
    delete ui;
}

void MorphoDialog::showEvent(QShowEvent *)
{
    if (showPreview)
        emit preview();
}

void MorphoDialog::on_comboType_currentIndexChanged(int index)
{
    processor->type = index;

    if (showPreview)
        emit preview();
}

void MorphoDialog::on_comboElement_currentIndexChanged(int index)
{
    processor->elem = index;

    if (showPreview)
        emit preview();
}

void MorphoDialog::on_sizeSlider_valueChanged(int value)
{
    processor->size = value;

    ui->sizeLabel->setText(tr("<p>Kernel Size:</p>"
                              "<p><b>%1</b></p>").arg(value));

    if (showPreview)
        emit preview();
}

void MorphoDialog::on_checkPreview_clicked()
{
    showPreview = !showPreview;
    if (showPreview)
        emit preview();
    else
        emit reset();
}








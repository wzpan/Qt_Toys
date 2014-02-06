#include "ErosionDialog.h"
#include "ui_ErosionDialog.h"

ErosionDialog::ErosionDialog(QWidget *parent, ErosionProcessor *processor) :
    QDialog(parent),
    ui(new Ui::ErosionDialog)
{
    this->processor = processor;
    ui->setupUi(this);

    ui->comboElement->setCurrentIndex(processor->elem);
    ui->sizeSlider->setValue(processor->size);
}

ErosionDialog::~ErosionDialog()
{
    delete ui;
}

void ErosionDialog::on_comboElement_currentIndexChanged(int index)
{
    processor->elem = index;
}

void ErosionDialog::on_sizeSlider_valueChanged(int value)
{
    processor->size = value;
    ui->sizeLabel->setText(tr("<p>Kernel Size:</p>"
                              "<p><b>%1</b></p>").arg(value));
}

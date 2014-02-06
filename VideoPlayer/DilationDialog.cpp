#include "DilationDialog.h"
#include "ui_DilationDialog.h"

DilationDialog::DilationDialog(QWidget *parent, DilationProcessor *processor) :
    QDialog(parent),
    ui(new Ui::DilationDialog)
{
    ui->setupUi(this);
    this->processor  = processor;

    ui->comboElement->setCurrentIndex(processor->elem);
    ui->sizeSlider->setValue(processor->size);
}

DilationDialog::~DilationDialog()
{
    delete ui;
}

void DilationDialog::on_sizeSlider_valueChanged(int value)
{
    processor->size = value;
    ui->sizeLabel->setText(tr("<p>Kernel Size:</p>"
                              "<p><b>%1</b></p>").arg(value));
}

void DilationDialog::on_comboElement_currentIndexChanged(int index)
{
    processor->elem = index;
}

#include "adjustdialog.h"
#include "ui_adjustdialog.h"

AdjustDialog::AdjustDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdjustDialog)
{
    ui->setupUi(this);

    type = 0;
    elem = 0;
    size = 0;
    showPreview = true;

    ui->comboType->setCurrentIndex(type);
    ui->comboElement->setCurrentIndex(elem);
    ui->sizeSlider->setValue(size);
    ui->checkPreview->setChecked(showPreview);
}

AdjustDialog::~AdjustDialog()
{
    delete ui;
}

void AdjustDialog::on_comboType_currentIndexChanged(int index)
{
    this->type = index;

    if (showPreview)
        emit preview();
}

void AdjustDialog::on_comboElement_currentIndexChanged(int index)
{
    this->elem = index;

    if (showPreview)
        emit preview();
}

void AdjustDialog::on_sizeSlider_valueChanged(int value)
{
    this->size = value;

    if (showPreview)
        emit preview();
}

void AdjustDialog::on_checkPreview_clicked()
{
    showPreview = !showPreview;
    if (showPreview)
        emit preview();
    else
        emit reset();
}








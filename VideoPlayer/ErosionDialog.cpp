#include "ErosionDialog.h"
#include "ui_ErosionDialog.h"

ErosionDialog::ErosionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErosionDialog)
{
    ui->setupUi(this);

    elem = 0;
    size = 3;

    ui->comboElement->setCurrentIndex(elem);
    ui->sizeSlider->setValue(size);
}

ErosionDialog::~ErosionDialog()
{
    delete ui;
}

void ErosionDialog::on_comboElement_currentIndexChanged(int index)
{
    elem = index;
}

void ErosionDialog::on_sizeSlider_valueChanged(int value)
{
    size = value;
    std::stringstream ss;
    ss << value;
    ui->sizeLabel->setText(QString::fromStdString(ss.str()));
}


int ErosionDialog::getSize()
{
    return size;
}

int ErosionDialog::getElem()
{
    return elem;
}

void ErosionDialog::setSize(int s)
{
    size = s;
}

void ErosionDialog::setElem(int e)
{
    elem = e;
}

void ErosionDialog::setParam(int s, int e)
{
    setSize(s);
    setElem(e);
}

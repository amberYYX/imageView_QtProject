#include "gaussrgbdialog.h"
#include "ui_gaussrgbdialog.h"
#include <iostream>
using namespace std;

GaussRgbDialog::GaussRgbDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GaussRgbDialog)
{
    ui->setupUi(this);
}

GaussRgbDialog::~GaussRgbDialog()
{
    delete ui;
}

void GaussRgbDialog::on_buttonBox_accepted()
{
    bool ok1,ok2;
    int size=ui->sizelineEdit->text().toInt(&ok1);
    double sigma=ui->sigmalineEdit->text().toDouble(&ok2);
    if (ok1&&ok2)
        emit confirmed(size,sigma);

    std::cout<<"GaussRGB size&sigma accepted"<<endl;
}

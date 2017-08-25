#include "gaussgraydialog.h"
#include "ui_gaussgraydialog.h"
#include <iostream>
using namespace std;

GaussGrayDialog::GaussGrayDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GaussGrayDialog)
{
    ui->setupUi(this);
}

GaussGrayDialog::~GaussGrayDialog()
{
    delete ui;
}

void GaussGrayDialog::on_buttonBox_accepted()
{
    bool ok1,ok2;
    int size=ui->sizelineEdit->text().toInt(&ok1);
    double sigma=ui->sigmalineEdit->text().toDouble(&ok2);
    if (ok1&&ok2)
        emit confirmed(size,sigma);

    std::cout<<"GaussGRAY size&sigma accepted"<<endl;
}

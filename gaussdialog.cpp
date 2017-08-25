#include "gaussdialog.h"
#include "ui_gaussdialog.h"
#include <iostream>
using namespace std;

GaussDialog::GaussDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GaussDialog)
{
    ui->setupUi(this);
}

GaussDialog::~GaussDialog()
{
    delete ui;
}

void GaussDialog::on_buttonBox_accepted()
{
    bool ok1,ok2;
    int size=ui->sizelineEdit->text().toInt(&ok1);
    double sigma=ui->sigmalineEdit->text().toDouble(&ok2);
    if (ok1&&ok2)
        emit confirmed(size,sigma);

    std::cout<<"size&sigma accepted"<<endl;
}

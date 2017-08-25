#include "bilateraldialog.h"
#include "ui_bilateraldialog.h"
#include <iostream>
using namespace std;

bilateralDialog::bilateralDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bilateralDialog)
{
    ui->setupUi(this);
}

bilateralDialog::~bilateralDialog()
{
    delete ui;
}

void bilateralDialog::on_buttonBox_accepted()
{
    bool ok1,ok2,ok3;
    int size = ui->sizeline->text().toInt(&ok1);
    double sigmaColor=ui->colorlineEdit->text().toDouble(&ok2);
    double sigmaSpace=ui->spacelineEdit->text().toDouble(&ok3);
    if (ok1 && ok2 && ok3)
        emit confirmed(size,sigmaColor,sigmaSpace);

    std::cout<<"size&sigma accepted"<<endl;
}

#include "loginformation.h"
#include "ui_loginformation.h"
#include <iostream>
using namespace std;

logInformation::logInformation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logInformation)
{
    ui->setupUi(this);
}

logInformation::~logInformation()
{
    delete ui;
}

void logInformation::on_buttonBox_accepted()
{
    bool ok;
    double c=ui->lineEdit->text().toDouble(&ok);
    if(ok)
        emit confirmed(c);

    std::cout<<"button box accepted"<<endl;
}

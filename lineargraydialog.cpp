#include "lineargraydialog.h"
#include "ui_lineargraydialog.h"
#include <iostream>
using namespace std;

LinearGrayDialog::LinearGrayDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LinearGrayDialog)
{
    ui->setupUi(this);
}

LinearGrayDialog::~LinearGrayDialog()
{
    delete ui;
}

void LinearGrayDialog::on_buttonBox_accepted()
{
    QString txt = ui->textEdit->toPlainText();
//    if(ok)//这里不需要判断，判断会报错
        emit confirmed(txt);

    std::cout<<"Linear GRAY accepted"<<endl;
}

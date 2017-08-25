#include "linearrgbdialog.h"
#include "ui_linearrgbdialog.h"
#include <iostream>
using namespace std;

LinearRgbDialog::LinearRgbDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LinearRgbDialog)
{
    ui->setupUi(this);
}

LinearRgbDialog::~LinearRgbDialog()
{
    delete ui;
}

void LinearRgbDialog::on_buttonBox_accepted()
{
    QString txt = ui->textEdit->toPlainText();
//    if(ok)//这里不需要判断，判断会报错
        emit confirmed(txt);

    std::cout<<"Linear RGB accepted"<<endl;
}

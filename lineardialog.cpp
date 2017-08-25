#include "lineardialog.h"
#include "ui_lineardialog.h"
#include <iostream>
using namespace std;

LinearDialog::LinearDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LinearDialog)
{
    ui->setupUi(this);
}

LinearDialog::~LinearDialog()
{
    delete ui;
}

//void LinearDialog::accept()
//{
//    emit confirmed(ui->textEdit->toPlainText());
//}

void LinearDialog::on_buttonBox_accepted()
{
    QString txt=ui->textEdit->toPlainText();
//    if(ok)//这里不需要判断，判断会报错
        emit confirmed(txt);

    std::cout<<"Linear accepted"<<endl;
}

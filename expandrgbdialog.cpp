#include "expandrgbdialog.h"
#include "ui_expandrgbdialog.h"
#include <iostream>
using namespace std;

ExpandRgbDialog::ExpandRgbDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExpandRgbDialog)
{
    ui->setupUi(this);
}

ExpandRgbDialog::~ExpandRgbDialog()
{
    delete ui;
}

void ExpandRgbDialog::on_buttonBox_accepted()
{
    bool ok;
    int e = ui->lineEdit->text().toDouble(&ok);
    if(ok)
        emit confirmed(e);

    std::cout<<"ExpandRgb e accepted"<<endl;
}

#include "expandgraydialog.h"
#include "ui_expandgraydialog.h"
#include <iostream>
using namespace std;

ExpandGrayDialog::ExpandGrayDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExpandGrayDialog)
{
    ui->setupUi(this);
}

ExpandGrayDialog::~ExpandGrayDialog()
{
    delete ui;
}

void ExpandGrayDialog::on_buttonBox_accepted()
{
    bool ok;
    int e = ui->lineEdit->text().toDouble(&ok);
    if(ok)
        emit confirmed(e);

    std::cout<<"ExpandGray e accepted"<<endl;
}

#include "expanddialog.h"
#include "ui_expanddialog.h"
#include <iostream>
using namespace std;

ExpandDialog::ExpandDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExpandDialog)
{
    ui->setupUi(this);
}

ExpandDialog::~ExpandDialog()
{
    delete ui;
}

void ExpandDialog::on_buttonBox_accepted()
{
    bool ok;
    int e = ui->lineEdit->text().toDouble(&ok);
    if(ok)
        emit confirmed(e);

    std::cout<<"Expand accepted"<<endl;
}

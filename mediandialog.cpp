#include "mediandialog.h"
#include "ui_mediandialog.h"
#include <iostream>
using namespace std;

MedianDialog::MedianDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MedianDialog)
{
    ui->setupUi(this);
}

MedianDialog::~MedianDialog()
{
    delete ui;
}

void MedianDialog::on_buttonBox_accepted()
{
    bool ok;
    double m = ui->lineEdit->text().toDouble(&ok);
    if(ok)
        emit confirmed(m);
    std::cout<<"median m accepted"<<endl;
}

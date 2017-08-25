#include "mediangraydialog.h"
#include "ui_mediangraydialog.h"
#include <iostream>
using namespace std;

MedianGrayDialog::MedianGrayDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MedianGrayDialog)
{
    ui->setupUi(this);
}

MedianGrayDialog::~MedianGrayDialog()
{
    delete ui;
}

void MedianGrayDialog::on_buttonBox_accepted()
{
    bool ok;
    double m = ui->lineEdit->text().toDouble(&ok);
    if(ok)
        emit confirmed(m);
    std::cout<<"MedianGray m accepted"<<endl;
}

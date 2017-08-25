#include "medianrgbdialog.h"
#include "ui_medianrgbdialog.h"
#include <iostream>
using namespace std;

MedianRgbDialog::MedianRgbDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MedianRgbDialog)
{
    ui->setupUi(this);
}

MedianRgbDialog::~MedianRgbDialog()
{
    delete ui;
}

void MedianRgbDialog::on_buttonBox_accepted()
{
    bool ok;
    double m = ui->lineEdit->text().toDouble(&ok);
    if(ok)
        emit confirmed(m);
    std::cout<<"MedianRgb m accepted"<<endl;
}

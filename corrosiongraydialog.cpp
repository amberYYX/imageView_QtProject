#include "corrosiongraydialog.h"
#include "ui_corrosiongraydialog.h"
#include <iostream>
using namespace std;

CorrosionGrayDialog::CorrosionGrayDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CorrosionGrayDialog)
{
    ui->setupUi(this);
}

CorrosionGrayDialog::~CorrosionGrayDialog()
{
    delete ui;
}

void CorrosionGrayDialog::on_buttonBox_accepted()
{
    bool ok;
    double co = ui->lineEdit->text().toDouble(&ok);
    if(ok)
        emit confirmed(co);
    std::cout<<"CorrosionGray co accepted"<<endl;
}

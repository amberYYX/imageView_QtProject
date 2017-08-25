#include "corrosionrgbdialog.h"
#include "ui_corrosionrgbdialog.h"
#include <iostream>
using namespace std;

CorrosionRgbDialog::CorrosionRgbDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CorrosionRgbDialog)
{
    ui->setupUi(this);
}

CorrosionRgbDialog::~CorrosionRgbDialog()
{
    delete ui;
}

void CorrosionRgbDialog::on_buttonBox_accepted()
{
    bool ok;
    double co = ui->lineEdit->text().toDouble(&ok);
    if(ok)
        emit confirmed(co);
    std::cout<<"CorrosionRGB co accepted"<<endl;
}

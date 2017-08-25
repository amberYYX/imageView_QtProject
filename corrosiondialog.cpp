#include "corrosiondialog.h"
#include "ui_corrosiondialog.h"
#include <iostream>
using namespace std;

CorrosionDialog::CorrosionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CorrosionDialog)
{
    ui->setupUi(this);
}

CorrosionDialog::~CorrosionDialog()
{
    delete ui;
}

void CorrosionDialog::on_buttonBox_accepted()
{
    bool ok;
    double co = ui->lineEdit->text().toDouble(&ok);
    if(ok)
        emit confirmed(co);
    std::cout<<"corrision co accepted"<<endl;
}

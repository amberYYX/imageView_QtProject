#include "hpdialog.h"
#include "ui_hpdialog.h"

hpDialog::hpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hpDialog)
{
    ui->setupUi(this);
}

hpDialog::~hpDialog()
{
    delete ui;
}

void hpDialog::on_buttonBox_accepted()
{
    bool  isOk;
    double c = ui->lineEdit->text().toDouble(&isOk);
    if(isOk){
        emit confirmed(c);
    }
}

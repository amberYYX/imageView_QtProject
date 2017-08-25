#include "lpdialog.h"
#include "ui_lpdialog.h"

lpDialog::lpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lpDialog)
{
    ui->setupUi(this);
}

lpDialog::~lpDialog()
{
    delete ui;
}

void lpDialog::on_buttonBox_accepted()
{
    bool  isOk;
    double c = ui->lineEdit->text().toDouble(&isOk);
    if(isOk){
        emit confirmed(c);
    }
}

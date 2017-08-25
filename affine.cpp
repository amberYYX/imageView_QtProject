#include "affine.h"
#include "ui_affine.h"
#include <iostream>
using namespace std;

affine::affine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::affine)
{
    ui->setupUi(this);
}

affine::~affine()
{
    delete ui;
}

void affine::on_buttonBox_accepted()
{
    QMatrix matrix;
    bool ok;
    qreal m11,m12,m21,m22,dx,dy;
    m11 = ui->inputbtn_11->text().toDouble(&ok);
    m12 = ui->inputbtn_12->text().toDouble(&ok);
    m21 = ui->inputbtn_21->text().toDouble(&ok);
    m21 = ui->inputbtn_22->text().toDouble(&ok);
    dx=0;
    dy=0;
    matrix.setMatrix(m11,m12,m21,m22,dx,dy);
    if(ok)
        emit confirmed(matrix);

    std::cout<<"affine matrix accepted"<<endl;
}

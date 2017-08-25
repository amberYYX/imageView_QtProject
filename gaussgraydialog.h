#ifndef GAUSSGRAYDIALOG_H
#define GAUSSGRAYDIALOG_H

#include <QDialog>

namespace Ui {
class GaussGrayDialog;
}

class GaussGrayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GaussGrayDialog(QWidget *parent = 0);
    ~GaussGrayDialog();

private slots:
    void on_buttonBox_accepted();

signals:
    void confirmed(int size,double sigma);

private:
    Ui::GaussGrayDialog *ui;
};

#endif // GAUSSGRAYDIALOG_H

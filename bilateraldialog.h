#ifndef BILATERALDIALOG_H
#define BILATERALDIALOG_H

#include <QDialog>

namespace Ui {
class bilateralDialog;
}

class bilateralDialog : public QDialog
{
    Q_OBJECT

public:
    explicit bilateralDialog(QWidget *parent = 0);
    ~bilateralDialog();

private:
    Ui::bilateralDialog *ui;

signals:
    void confirmed(int size,double sigmaColor,double sigmaSpace);
private slots:
    void on_buttonBox_accepted();
};

#endif // BILATERALDIALOG_H

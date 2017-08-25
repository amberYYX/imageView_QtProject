#ifndef HPDIALOG_H
#define HPDIALOG_H

#include <QDialog>

namespace Ui {
class hpDialog;
}

class hpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit hpDialog(QWidget *parent = 0);
    ~hpDialog();

private slots:
    void on_buttonBox_accepted();
signals:
    void confirmed(double);


private:
    Ui::hpDialog *ui;
};

#endif // HPDIALOG_H

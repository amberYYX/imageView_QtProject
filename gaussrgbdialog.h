#ifndef GAUSSRGBDIALOG_H
#define GAUSSRGBDIALOG_H

#include <QDialog>

namespace Ui {
class GaussRgbDialog;
}

class GaussRgbDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GaussRgbDialog(QWidget *parent = 0);
    ~GaussRgbDialog();

private slots:
    void on_buttonBox_accepted();

signals:
    void confirmed(int size,double sigma);

private:
    Ui::GaussRgbDialog *ui;
};

#endif // GAUSSRGBDIALOG_H

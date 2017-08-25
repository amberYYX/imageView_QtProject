#ifndef GAUSSDIALOG_H
#define GAUSSDIALOG_H

#include <QDialog>

namespace Ui {
class GaussDialog;
}

class GaussDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GaussDialog(QWidget *parent = 0);
    ~GaussDialog();

private:
    Ui::GaussDialog *ui;

signals:
    void confirmed(int size,double sigma);
private slots:
    void on_buttonBox_accepted();
};

#endif // GAUSSDIALOG_H

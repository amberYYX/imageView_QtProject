#ifndef LPDIALOG_H
#define LPDIALOG_H

#include <QDialog>

namespace Ui {
class lpDialog;
}

class lpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit lpDialog(QWidget *parent = 0);
    ~lpDialog();

private slots:
    void on_buttonBox_accepted();
signals:
    void confirmed(double);

private:
    Ui::lpDialog *ui;
};

#endif // LPDIALOG_H

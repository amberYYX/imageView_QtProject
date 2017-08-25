#ifndef LINEARDIALOG_H
#define LINEARDIALOG_H

#include <QDialog>

namespace Ui {
class LinearDialog;
}

class LinearDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LinearDialog(QWidget *parent = 0);
    ~LinearDialog();

//    void accept();

private:
    Ui::LinearDialog *ui;

signals:
    void confirmed(QString);
private slots:
    void on_buttonBox_accepted();

};

#endif // LINEARDIALOG_H

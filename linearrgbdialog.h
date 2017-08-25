#ifndef LINEARRGBDIALOG_H
#define LINEARRGBDIALOG_H

#include <QDialog>

namespace Ui {
class LinearRgbDialog;
}

class LinearRgbDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LinearRgbDialog(QWidget *parent = 0);
    ~LinearRgbDialog();


private slots:
    void on_buttonBox_accepted();

signals:
    void confirmed(QString);
private:
    Ui::LinearRgbDialog *ui;
};

#endif // LINEARRGBDIALOG_H

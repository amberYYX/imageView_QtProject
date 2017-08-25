#ifndef EXPANDRGBDIALOG_H
#define EXPANDRGBDIALOG_H

#include <QDialog>

namespace Ui {
class ExpandRgbDialog;
}

class ExpandRgbDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExpandRgbDialog(QWidget *parent = 0);
    ~ExpandRgbDialog();

private:
    Ui::ExpandRgbDialog *ui;
signals:
    void confirmed(double);
private slots:
    void on_buttonBox_accepted();
};

#endif // EXPANDRGBDIALOG_H

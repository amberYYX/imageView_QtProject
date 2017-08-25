#ifndef CORROSIONRGBDIALOG_H
#define CORROSIONRGBDIALOG_H

#include <QDialog>

namespace Ui {
class CorrosionRgbDialog;
}

class CorrosionRgbDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CorrosionRgbDialog(QWidget *parent = 0);
    ~CorrosionRgbDialog();

private:
    Ui::CorrosionRgbDialog *ui;

signals:
   void confirmed(double);
private slots:
   void on_buttonBox_accepted();
};

#endif // CORROSIONRGBDIALOG_H

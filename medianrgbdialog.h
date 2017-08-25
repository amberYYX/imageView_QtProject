#ifndef MEDIANRGBDIALOG_H
#define MEDIANRGBDIALOG_H

#include <QDialog>

namespace Ui {
class MedianRgbDialog;
}

class MedianRgbDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MedianRgbDialog(QWidget *parent = 0);
    ~MedianRgbDialog();

private slots:
    void on_buttonBox_accepted();

signals:
   void confirmed(double);

private:
    Ui::MedianRgbDialog *ui;
};

#endif // MEDIANRGBDIALOG_H

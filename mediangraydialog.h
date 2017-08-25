#ifndef MEDIANGRAYDIALOG_H
#define MEDIANGRAYDIALOG_H

#include <QDialog>

namespace Ui {
class MedianGrayDialog;
}

class MedianGrayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MedianGrayDialog(QWidget *parent = 0);
    ~MedianGrayDialog();

private slots:
    void on_buttonBox_accepted();

signals:
    void confirmed(double);

private:
    Ui::MedianGrayDialog *ui;
};

#endif // MEDIANGRAYDIALOG_H

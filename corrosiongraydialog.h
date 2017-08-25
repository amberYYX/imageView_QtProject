#ifndef CORROSIONGRAYDIALOG_H
#define CORROSIONGRAYDIALOG_H

#include <QDialog>

namespace Ui {
class CorrosionGrayDialog;
}

class CorrosionGrayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CorrosionGrayDialog(QWidget *parent = 0);
    ~CorrosionGrayDialog();

private:
    Ui::CorrosionGrayDialog *ui;

signals:
   void confirmed(double);
private slots:
   void on_buttonBox_accepted();
};

#endif // CORROSIONGRAYDIALOG_H

#ifndef EXPANDGRAYDIALOG_H
#define EXPANDGRAYDIALOG_H

#include <QDialog>

namespace Ui {
class ExpandGrayDialog;
}

class ExpandGrayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExpandGrayDialog(QWidget *parent = 0);
    ~ExpandGrayDialog();

private:
    Ui::ExpandGrayDialog *ui;

signals:
    void confirmed(double);
private slots:
    void on_buttonBox_accepted();
};

#endif // EXPANDGRAYDIALOG_H

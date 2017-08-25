#ifndef EXPANDDIALOG_H
#define EXPANDDIALOG_H

#include <QDialog>

namespace Ui {
class ExpandDialog;
}

class ExpandDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExpandDialog(QWidget *parent = 0);
    ~ExpandDialog();

private:
    Ui::ExpandDialog *ui;

signals:
    void confirmed(double);
private slots:
    void on_buttonBox_accepted();
};

#endif // EXPANDDIALOG_H

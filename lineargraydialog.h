#ifndef LINEARGRAYDIALOG_H
#define LINEARGRAYDIALOG_H

#include <QDialog>

namespace Ui {
class LinearGrayDialog;
}

class LinearGrayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LinearGrayDialog(QWidget *parent = 0);
    ~LinearGrayDialog();

private slots:
    void on_buttonBox_accepted();

signals:
    void confirmed(QString);

private:
    Ui::LinearGrayDialog *ui;
};

#endif // LINEARGRAYDIALOG_H

#ifndef MEDIANDIALOG_H
#define MEDIANDIALOG_H

#include <QDialog>

namespace Ui {
class MedianDialog;
}

class MedianDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MedianDialog(QWidget *parent = 0);
    ~MedianDialog();

private:
    Ui::MedianDialog *ui;

 signals:
    void confirmed(double);
private slots:
    void on_buttonBox_accepted();
};

#endif // MEDIANDIALOG_H

#ifndef LOGINFORMATION_H
#define LOGINFORMATION_H

#include <QDialog>

namespace Ui {
class logInformation;
}

class logInformation : public QDialog
{
    Q_OBJECT

public:
    explicit logInformation(QWidget *parent = 0);
    ~logInformation();

private:
    Ui::logInformation *ui;

signals:
    void confirmed(double);
private slots:
    void on_buttonBox_accepted();
};

#endif // LOGINFORMATION_H

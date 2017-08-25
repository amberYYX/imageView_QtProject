#ifndef AFFINE_H
#define AFFINE_H

#include <QDialog>

namespace Ui {
class affine;
}

class affine : public QDialog
{
    Q_OBJECT

public:
    explicit affine(QWidget *parent = 0);
    ~affine();

private slots:
    void on_buttonBox_accepted();

signals:
    void confirmed(QMatrix);

private:
    Ui::affine *ui;
};

#endif // AFFINE_H

#ifndef MYQIMAGE_H
#define MYQIMAGE_H

#include <QObject>
#include <QImage>

class MyQImage : public QObject,public QImage
{
    Q_OBJECT
public:
//    explicit MyQImage(QObject *parent = 0);
      explicit MyQImage(QImage *parent = 0);

signals:

public slots:

public:
    void rgb2gray();
};

#endif // MYQIMAGE_H

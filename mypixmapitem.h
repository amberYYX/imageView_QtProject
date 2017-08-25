#ifndef MYPIXMAPITEM_H
#define MYPIXMAPITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>

class MyPixmapItem : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
//    explicit MyPixmapItem(QObject *parent = 0);
    explicit MyPixmapItem(QGraphicsPixmapItem *parent = 0);

signals:

public slots:

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void wheelEvent(QGraphicsSceneWheelEvent *event);
    const double RATA;

public :
    void itemReset();
};

#endif // MYPIXMAPITEM_H

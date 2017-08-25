#include "mypixmapitem.h"

#include <iostream>
using namespace std;

//MyPixmapItem::MyPixmapItem(QGraphicsPixmapItem *parent) :
//    QGraphicsPixmapItem(parent)
MyPixmapItem::MyPixmapItem(QGraphicsPixmapItem *parent) :
    QGraphicsPixmapItem(parent),
    RATA(0.1)
{

}

void MyPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   cout<<"PRESS"<<endl;
}


void MyPixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    setPos(pos()+mapToParent(event->pos())-
                             mapToParent(event->lastPos()));

    cout<<"MOVE"<<endl;
}


void MyPixmapItem::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    int delta=event->delta();
    double factor=scale();
    if(delta>0)
        factor*=(1+RATA);
    if(delta<0)
        factor*=(1-RATA);
    setTransformOriginPoint(boundingRect().width()/2,
                            boundingRect().height()/2);//设置缩放中心

    setScale(factor);

    cout<<"wheel"<<endl;
}

void MyPixmapItem::itemReset()
{
    setPos(0,0);
    setScale(1.0);
}

#include "rectitem.h"

RectItem::RectItem() : QGraphicsItem()
{
    this->setFlag( QGraphicsItem::ItemIsMovable );
}

void RectItem::SetRect(QPoint p1, QPoint p2)
{
    point1 = p1;
    point2 = p2;
}

QRectF RectItem::boundingRect() const
{
    return QRectF( 0, 0, 10, 10 );
}

void RectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem* option, QWidget *widget)
{
    painter->drawLine( point1, point2 );
}



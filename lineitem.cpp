#include "lineitem.h"

LineItem::LineItem() : QGraphicsItem()
{
}

QRectF LineItem::boundingRect() const
{
    return QRectF( 0, 0, 10, 10 );
}

void LineItem::SetRect(QPoint p1, QPoint p2)
{
    point1 = p1;
    point2 = p2;
}

void LineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem* option, QWidget *widget)
{
    painter->drawRect( QRect( point1, point2 ) );
}

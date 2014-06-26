#ifndef LINEITEM_H
#define LINEITEM_H

#include <QGraphicsItem>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>

class LineItem : public QGraphicsItem
{
public:
    LineItem();
    QRectF boundingRect() const;
    void SetRect( QPoint p1, QPoint p2 );
    void paint( QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget* widget );

private:


private:
    QPoint point1;
    QPoint point2;

    QPen pen;

};

#endif // LINEITEM_H

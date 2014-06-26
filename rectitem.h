#ifndef RECTITEM_H
#define RECTITEM_H

#include <QGraphicsItem>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QStyleOptionGraphicsItem>

class RectItem : public QGraphicsItem
{
    Q_OBJECT
public:
    RectItem();
    void SetRect( QPoint p1, QPoint p2 );
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem* option, QWidget *widget);
signals:

public slots:


private:
    QPoint point1;
    QPoint point2;

    QPen pen;

};

#endif // RECTITEM_H

#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <qmath.h>

class MyScene : public QGraphicsScene
{
public:
    MyScene();
    QPointF GetPoint() const;
    void SetCursorStatus( bool cursor );
    QGraphicsView* GetView();

    void setLineButClicked( bool status );
    void setEllButClicked( bool status );
    void setRectButClicked( bool status );

    bool getLineButClicked() const;
    bool getEllButClicked() const;
    bool getRectButClicked() const;
protected:
    virtual void mousePressEvent( QGraphicsSceneMouseEvent* event );
    virtual void mouseReleaseEvent( QGraphicsSceneMouseEvent* event );
    virtual void mouseDoubleClickEvent( QGraphicsSceneMouseEvent* event );
private:
    void unselectAllGraphicItems();
private:
    // Save mouse point
    QPointF point;
    QPointF oldpoint;
    // New Figure Coords
    QPointF transformP1;
    QPointF transformP2;

    bool ArrowCursor;
    bool Transform;

    bool lineButClicked;
    bool rectButClicked;
    bool ellButClicked;

    QGraphicsItem* curItem;
    QGraphicsItem* newItem;
    QGraphicsView* view;
};

#endif // MYSCENE_H

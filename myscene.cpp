#include "myscene.h"

MyScene::MyScene() : ArrowCursor( false ), Transform( false ), lineButClicked( false ), ellButClicked( false ),
    rectButClicked( false )
{
    view = new QGraphicsView( this );
    view->showMaximized();
    view->show();
    view->setRenderHint( QPainter::Antialiasing );
}

QPointF MyScene::GetPoint() const
{
    return point;
}

void MyScene::SetCursorStatus(bool cursor)
{
    ArrowCursor = cursor;
}

QGraphicsView *MyScene::GetView()
{
    return view;
}

void MyScene::setLineButClicked(bool status)
{
    lineButClicked = status;
}

void MyScene::setEllButClicked(bool status)
{
    ellButClicked = status;
}

void MyScene::setRectButClicked(bool status)
{
    rectButClicked = status;
}

bool MyScene::getLineButClicked() const
{
    return lineButClicked;
}

bool MyScene::getEllButClicked() const
{
    return ellButClicked;
}

bool MyScene::getRectButClicked() const
{
    return rectButClicked;
}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   point = event->scenePos();
   if( ArrowCursor )
   {
      curItem = this->itemAt( point, view->transform() );
      if( curItem )
      {
         if( curItem->isSelected() )
         {
             Transform = true;
             transformP1 = event->scenePos();
         }
         else
         {
              unselectAllGraphicItems();
              curItem->setSelected( true );
         }

      }
      else
      {
          unselectAllGraphicItems();
      }

   }
}

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if( Transform )
    {
        transformP2 = event->scenePos();

        QRectF oldRect = curItem->boundingRect();
        QRectF newRect = QRectF( transformP1, transformP2 );
        // Get right scale
        double scaleX = newRect.width() / oldRect.width();
        double scaleY = newRect.height() / oldRect.height();

        curItem->setTransform( QTransform::fromScale( scaleX, scaleY ), true );
        curItem->setSelected( false );
        curItem->setPos( oldRect.topLeft() );
        Transform = false;
    }
}

void MyScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED( event );
    if( curItem && curItem->isSelected() )
    {
        this->removeItem( curItem );
    }
}

void MyScene::unselectAllGraphicItems()
{
    // Get all selected items
    QList<QGraphicsItem*> tempList = this->selectedItems();
    for( int i = 0; i < tempList.size();i++ )
    {
        tempList[i]->setSelected( false );
    }
}


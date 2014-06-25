#ifndef MYPAINT_H
#define MYPAINT_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QLabel>
#include <QVector>
#include <QPoint>
#include <QComboBox>
#include <QPen>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

namespace Ui {
class MyPaint;
}

class MyPaint : public QDialog
{
    Q_OBJECT

public:
    explicit MyPaint(QWidget *parent = 0);
    ~MyPaint();

private slots:
    void lineButtonClicked();
    void ellButtonClicked();
    void rectButtonClicked();

protected:
    virtual void mousePressEvent( QMouseEvent  *event);

private:
    void InitializeButtons();
    void InitializeButton( QPushButton*& button, QString iconStr );
    void InitializeLayouts();
    void InitializePenBox();

    void paintEvent( QPaintEvent * pe );
    void PushBackPoint( QPoint mousePos );

private:
    Ui::MyPaint *ui;

    //Layouts
    QHBoxLayout* frontLayout;
    QVBoxLayout* buttonLayout;
    QLayout* paintLayout;

    // Pen color list
    QComboBox* penBox;

    QPen pen;

    //Buttons
    QPushButton* lineButton;
    QPushButton* rectButton;
    QPushButton* ellButton;

    QLabel* label;

    // Checks
    bool lineButClicked;
    bool rectButClicked;
    bool ellButClicked;
    bool Paint;

    //Graphic View & Scene
    QGraphicsView* view;
    QGraphicsScene* scene;

    // Save position of all geometry
    QVector< QVector<QPoint> > geom;
    // Save object
    QVector< QGraphicsItem* > items;
    // Index to current figure
    int index;
    // Points to make figure
    int pointsNum;
};

#endif // MYPAINT_H

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

private:
    void InitializeButtons();
    void InitializeButton( QPushButton*& button, QString iconStr );
    void InitializeLayouts();
    void mousePressEvent( QMouseEvent* event );
    void paintEvent( QPaintEvent * pe );
    void PushBackPoint( QPoint mousePos );

private:
    Ui::MyPaint *ui;

    //Layouts
    QHBoxLayout* frontLayout;
    QVBoxLayout* buttonLayout;
    QLayout* paintLayout;

    //Buttons
    QPushButton* lineButton;
    QPushButton* rectButton;
    QPushButton* ellButton;

    bool lineButClicked;
    bool rectButClicked;
    bool ellButClicked;

    //Graphic View
    QGraphicsView* view;
    QGraphicsScene* scene;
    QGraphicsItem* item;

    // Points to make geometry
    QPoint pointStart;
    QPoint pointEnd;

    // Save position of all geometry
    QVector< QVector<QPoint> > geom;
    // Index to current figure
    int index;
    // Points to make figure
    int pointsNum;
};

#endif // MYPAINT_H

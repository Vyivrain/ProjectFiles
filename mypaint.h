#ifndef MYPAINT_H
#define MYPAINT_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMouseEvent>
#include <QLabel>
#include <QComboBox>
#include <QVector>
#include <QLabel>
#include <QFileDialog>

#include "myscene.h"


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
    void SaveImage();
    void OpenImage();

protected:
    virtual void mousePressEvent( QMouseEvent  *event);

private:
    void InitializeButtons();
    void InitializeButton( QPushButton*& button, QString iconStr );
    void InitializeLayouts();
    void InitializePenBox();
    void SetPenColor( int index );


    void paintEvent( QPaintEvent * pe );

private:
    Ui::MyPaint *ui;

    //Layouts
    QHBoxLayout* frontLayout;
    QVBoxLayout* buttonLayout;
    QVBoxLayout* penLayout;
    QVBoxLayout* onlyButLayout;
    QLayout* paintLayout;

    // Pen color list
    QComboBox* penBox;

    QPen pen;

    //Buttons
    QPushButton* lineButton;
    QPushButton* rectButton;
    QPushButton* ellButton;
    QPushButton* saveButton;
    QPushButton* openButton;

    QLabel* label;

    // Checks
    bool lineButClicked;
    bool rectButClicked;
    bool ellButClicked;
    bool Paint;

    bool GraphicEvent;

    //Graphic View & Scene

    MyScene* myscene;
    QGraphicsView* view;
    QGraphicsItem* item;
    // Save position of all geometry
    QVector< QVector<QPoint> > geom;

    QPoint point1;
    QPoint point2;
    // Index to current figure
    int index;
    // Points to make figure
    int pointsNum;

    QFileDialog* FileDial;

};

#endif // MYPAINT_H

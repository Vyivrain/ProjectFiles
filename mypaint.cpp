#include "mypaint.h"
#include "ui_mypaint.h"

MyPaint::MyPaint(QWidget *parent) :
    QDialog(parent),lineButClicked( false ), ellButClicked( false ),
    rectButClicked( false ), index( 0 ), pointsNum( 0 ),
    ui(new Ui::MyPaint)
{
    ui->setupUi(this);
    geom.resize( 1 );
    InitializeLayouts();
    InitializeButtons();

    scene = new QGraphicsScene();
    view = new QGraphicsView( scene );
    view->showMaximized();

    paintLayout->addWidget( view );

    setLayout( frontLayout );
}

MyPaint::~MyPaint()
{
    delete ui;
}

void MyPaint::lineButtonClicked()
{
    // Button isn't pressed
    if( !lineButClicked )
    {
        lineButClicked = true;

        if( ellButClicked )
        {
            ellButClicked = false;
            ellButton->setChecked( false );
        }
        if( rectButClicked )
        {
            rectButClicked = false;
            rectButton->setChecked( false );
        }
        view->setCursor( Qt::CrossCursor );
    }
    // Button is pressed
    else
    {
        lineButClicked = false;

        view->setCursor( Qt::ArrowCursor );
    }
}

void MyPaint::ellButtonClicked()
{
    // Button isn't pressed
    if( !ellButClicked )
    {
        ellButClicked = true;

        if( lineButClicked )
        {
            lineButClicked = false;
            lineButton->setChecked( false );
        }
        if( rectButClicked )
        {
            rectButClicked = false;
            rectButton->setChecked( false );
        }
        view->setCursor( Qt::CrossCursor );
    }
    // Button is pressed
    else
    {
        ellButClicked = false;

        view->setCursor( Qt::ArrowCursor );
    }
}

void MyPaint::rectButtonClicked()
{
    // Button isn't pressed
    if( !rectButClicked )
    {
        rectButClicked = true;

        if( lineButClicked )
        {
            lineButClicked = false;
            lineButton->setChecked( false );
        }
        if( ellButClicked )
        {
            ellButClicked = false;
            ellButton->setChecked( false );
        }
        view->setCursor( Qt::CrossCursor );
    }
    // Button is pressed
    else
    {
        rectButClicked = false;

        view->setCursor( Qt::ArrowCursor );
    }
}

void MyPaint::InitializeButtons()
{
    // Initialize buttons
    InitializeButton( lineButton, "Line.jpg" );
    InitializeButton( ellButton, "Ellipse.png" );
    InitializeButton( rectButton, "Rect.png" );

    // Set connections
    connect( lineButton, SIGNAL(clicked()), this, SLOT( lineButtonClicked() ) );
    connect( ellButton, SIGNAL(clicked()), this, SLOT( ellButtonClicked() ) );
    connect( rectButton, SIGNAL(clicked()), this, SLOT( rectButtonClicked() ) );

}

void MyPaint::InitializeButton(QPushButton *&button, QString iconStr)
{
     button = new QPushButton();
     button->setCheckable( true );
     button->setIcon( QIcon( iconStr ) );
     buttonLayout->addWidget( button );
}

void MyPaint::InitializeLayouts()
{
    frontLayout = new QHBoxLayout();
    buttonLayout = new QVBoxLayout();
    paintLayout = new QVBoxLayout();

    frontLayout->addLayout( buttonLayout );
    frontLayout->addLayout( paintLayout );
}

void MyPaint::mousePressEvent(QMouseEvent *event)
{
    if( event->button() == Qt::LeftButton && view->cursor().shape() == Qt::CrossCursor )
    {
        switch( pointsNum )
        {
        case 0:
            geom.push_back( QVector<QPoint>() );
            PushBackPoint( event->pos() );
        break;

        case 1:
            PushBackPoint( event->pos() );
            if( lineButClicked || ellButClicked || rectButClicked )
                this->update();

        break;
        }
    }
}

void MyPaint::paintEvent(QPaintEvent *pe)
{
    QPainter painter( this );
    if( lineButClicked )
    {
        painter.drawLine( geom[index][0], geom[index][1] );
        index++;
        pointsNum = 0;
    }
    else if( ellButClicked )
    {
        painter.drawRect( QRect( geom[index][0], geom[index][1] ) );
        index++;
        pointsNum = 0;
    }
    else if ( rectButClicked )
    {
        painter.drawEllipse( QRect( geom[index][0], geom[index][1] ) );
        index++;
        pointsNum = 0;
    }
}

void MyPaint::PushBackPoint( QPoint mousePos )
{
    pointsNum++;
    geom[index].push_back( mousePos );
}

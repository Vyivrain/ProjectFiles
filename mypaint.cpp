#include "mypaint.h"
#include "ui_mypaint.h"

MyPaint::MyPaint(QWidget *parent) :
    QDialog(parent),lineButClicked( false ), ellButClicked( false ),
    rectButClicked( false ), index( 0 ), pointsNum( 0 ), Paint( false ),
    ui(new Ui::MyPaint)
{
    ui->setupUi(this);

    //Initialize pen list
    penBox = new QComboBox();

    //Initialize pen
    pen = QPen( QColor( 0, 0, 0 ) );

    InitializeLayouts();
    InitializePenBox();
    InitializeButtons();

    // Create scene and a view for painting
    scene = new QGraphicsScene();
    view = new QGraphicsView( scene );
    view->showMaximized();
    view->centerOn( view->rect().left(), view->rect().top() );
    view->show();


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

    label = new QLabel();
    buttonLayout->addWidget( label );

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

void MyPaint::InitializePenBox()
{
    penBox->addItem( QIcon( "black.jpg" ), "black" );
    penBox->addItem( QIcon( "red.jpg" ), "red" );
    penBox->addItem( QIcon( "blue.jpg" ), "blue" );
    penBox->addItem( QIcon( "green.jpg" ), "green" );
    penBox->addItem( QIcon( "grey.jpg" ), "gray" );
    penBox->addItem( QIcon( "yellow.jpg" ), "yellow" );

    buttonLayout->addWidget( penBox );
}

void MyPaint::mousePressEvent(QMouseEvent  *event)
{
    if( event->button() == Qt::LeftButton && view->cursor().shape() == Qt::CrossCursor )
    {
        switch( pointsNum )
        {
        case 0:
            // Create new point for figure with 2 points
            geom.push_back( QVector<QPoint>() );
            // pushback coords of the mouse click
            PushBackPoint(  event->pos() );
        break;

        case 1:
            PushBackPoint( event->pos()  );

            if( lineButClicked || ellButClicked || rectButClicked )
            {
                Paint = true;
                switch( penBox->currentIndex() )
                {
                    case 0:
                        pen.setColor( Qt::black );
                    break;
                    case 1:
                        pen.setColor( Qt::red );
                    break;
                    case 2:
                        pen.setColor( Qt::blue );
                    break;
                    case 3:
                        pen.setColor( Qt::green );
                    break;
                    case 4:
                        pen.setColor( Qt::gray );
                    break;
                    case 5:
                        pen.setColor( Qt::yellow );
                    break;

                    default:
                    break;
                }


                this->update();
            }
        break;
        }
    }
}

void MyPaint::paintEvent(QPaintEvent *pe)
{
    if( Paint )
    {
        QPainter painter( this );
        QPoint temp( view->pos() );
        QPoint correct( view->rect().width() / 2, view->rect().height() / 2 );
        if( lineButClicked )
        {

            items.push_back( scene->addLine( QLine(
                  geom[index][0] - temp - correct,
                  geom[index][1] - temp - correct   ), pen ) );

            items[index]->setFlag( QGraphicsItem::ItemIsMovable );

            index++;
            pointsNum = 0;
        }
        else if( ellButClicked )
        {
            scene->addRect( QRect( geom[index][0] - temp, geom[index][1] - temp ),
                    pen );
            index++;
            pointsNum = 0;
        }
        else if ( rectButClicked )
        {
            scene->addEllipse( QRect( geom[index][0], geom[index][1] ), pen );
            index++;
            pointsNum = 0;
        }
        Paint = false;
    }
}

void MyPaint::PushBackPoint( QPoint mousePos )
{
    pointsNum++;
    geom[index].push_back( mousePos );
}

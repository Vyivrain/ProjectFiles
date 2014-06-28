#include "mypaint.h"
#include "ui_mypaint.h"

MyPaint::MyPaint(QWidget *parent) :
    QDialog(parent),lineButClicked( false ), ellButClicked( false ),
    rectButClicked( false ), index( 0 ), pointsNum( 0 ), Paint( false ),
    GraphicEvent( false ),
    ui(new Ui::MyPaint)
{
    ui->setupUi(this);

    //Initialize pen list
    penBox = new QComboBox();
    //Initialize pen
    pen = QPen( QColor( 0, 0, 0 ) );
    pen.setCosmetic( true );
    // Initialize Layouts, boxes, buttons
    InitializeLayouts();
    InitializePenBox();
    InitializeButtons();

    FileDial = new QFileDialog( this,
                                tr("Save File"),
                                "C://",
                                "Images (*.png)" );

    myscene = new MyScene();
    view = myscene->GetView();
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
    if( !myscene->getLineButClicked() )
    {
        myscene->setLineButClicked( true );

        if( myscene->getEllButClicked() )
        {
            myscene->setEllButClicked( false );
            ellButton->setChecked( false );
        }
        if( myscene->getRectButClicked() )
        {
            myscene->setRectButClicked( false );
            rectButton->setChecked( false );
        }
        view->setCursor( Qt::CrossCursor );
    }
    // Button is pressed
    else
    {
         myscene->setLineButClicked( false );

        view->setCursor( Qt::ArrowCursor );
    }
}

void MyPaint::ellButtonClicked()
{
    // Button isn't pressed
    if( !myscene->getEllButClicked() )
    {
        myscene->setEllButClicked( true );

        if( myscene->getLineButClicked() )
        {
            myscene->setLineButClicked( false );
            lineButton->setChecked( false );
        }
        if( myscene->getRectButClicked() )
        {
            myscene->setRectButClicked( false );
            rectButton->setChecked( false );
        }
        view->setCursor( Qt::CrossCursor );
    }
    // Button is pressed
    else
    {
        myscene->setEllButClicked( false );

        view->setCursor( Qt::ArrowCursor );
    }
}

void MyPaint::rectButtonClicked()
{
    // Button isn't pressed
    if( !myscene->getRectButClicked() )
    {
        myscene->setRectButClicked( true );

        if(  myscene->getLineButClicked() )
        {
            myscene->setLineButClicked( false );
            lineButton->setChecked( false );
        }
        if( myscene->getEllButClicked() )
        {
            myscene->setEllButClicked( false );
            ellButton->setChecked( false );
        }
        view->setCursor( Qt::CrossCursor );
    }
    // Button is pressed
    else
    {
        myscene->setRectButClicked( false );

        view->setCursor( Qt::ArrowCursor );
    }
}

void MyPaint::SaveImage()
{
    QString fileName = FileDial->getSaveFileName( this,
                                                  tr("Save File"),
                                                  "C://",
                                                  "Images (*.png)" );


    myscene->clearSelection();
    myscene->setSceneRect( myscene->itemsBoundingRect() );

    QImage image( myscene->sceneRect().size().toSize(), QImage::Format_ARGB32 );
    image.fill( Qt::transparent );

    QPainter painter( &image );
    myscene->render( &painter );
    image.save( fileName );

}

void MyPaint::OpenImage()
{
    QString fileName = FileDial->getOpenFileName( this,
                                                  tr("Save File"),
                                                  "C://",
                                                  "Images (*.png)" );

    QImage image( fileName );
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem( QPixmap::fromImage( image ) );
    item->setPos( 0, 0 );
    item->setFlags( QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable );
    myscene->addItem( item );

}

void MyPaint::InitializeButtons()
{
    // Initialize buttons
    InitializeButton( lineButton, "Line.jpg" );
    InitializeButton( ellButton, "Ellipse.png" );
    InitializeButton( rectButton, "Rect.png" );

    saveButton = new QPushButton( "Save image" );
    openButton = new QPushButton( "Open image" );

    buttonLayout->addWidget( saveButton );
    buttonLayout->addWidget( openButton );

    // Set connections
    connect( lineButton, SIGNAL(clicked()), this, SLOT( lineButtonClicked() ) );
    connect( ellButton, SIGNAL(clicked()), this, SLOT( ellButtonClicked() ) );
    connect( rectButton, SIGNAL(clicked()), this, SLOT( rectButtonClicked() ) );
    connect( saveButton, SIGNAL(clicked()), this, SLOT( SaveImage()) );
    connect( openButton, SIGNAL(clicked()), this, SLOT( OpenImage()) );
}

void MyPaint::InitializeButton(QPushButton *&button, QString iconStr)
{
     button = new QPushButton();
     button->setCheckable( true );
     button->setIcon( QIcon( iconStr ) );
     onlyButLayout->addWidget( button );
}

void MyPaint::InitializeLayouts()
{
    frontLayout = new QHBoxLayout();
    buttonLayout = new QVBoxLayout();
    paintLayout = new QVBoxLayout();
    onlyButLayout = new QVBoxLayout();
    penLayout = new QVBoxLayout();


    label = new QLabel( "Set Pen Color:" );
    label->setFixedSize( 70, 10 );
    penLayout->addWidget( label );

    penLayout->addSpacing( 0 );
    buttonLayout->addSpacing( 5 );

    buttonLayout->addLayout( penLayout );
    buttonLayout->addLayout( onlyButLayout );
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

    penLayout->addWidget( penBox );
}

void MyPaint::SetPenColor(int index)
{
    switch( index )
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
}

void MyPaint::mousePressEvent(QMouseEvent  *event)
{
    if( event->button() == Qt::LeftButton )
    {
        if( view->cursor().shape() == Qt::CrossCursor )
        {
            switch( pointsNum )
            {
            case 0:
                // Save 1 position
                point1 = myscene->GetPoint().toPoint();

                SetPenColor( penBox->currentIndex() );

                // go to another case
                pointsNum++;

            break;

            case 1:
                // Save 2 position
                point2 = myscene->GetPoint().toPoint();
                // Go to 3 point if needed
                pointsNum++;
                if( myscene->getLineButClicked() || myscene->getEllButClicked() || myscene->getRectButClicked() )
                {
                    // Ready for painting
                    Paint = true;

                    // Call repaint
                    this->update();
                }
            break;
            }
        }
        else
        {
            myscene->SetCursorStatus( true );
        }
    }
}

void MyPaint::paintEvent(QPaintEvent *pe)
{
    Q_UNUSED( pe );
    if( Paint )
    { 
        if( myscene->getLineButClicked() )
        {
            item = myscene->addLine( QLine( point1, point2 ), pen );

            item->setFlags( QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable );

            index++;
            pointsNum = 0;
        }
        else if( myscene->getEllButClicked() )
        {
            item = myscene->addEllipse( QRect( point1, point2 ), pen ) ;

             item->setFlags( QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable );

             index++;
            pointsNum = 0;
        }
        else if ( myscene->getRectButClicked() )
        {
            item = myscene->addRect( QRect( point1, point2 ), pen );

            item->setFlags( QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable );

            index++;
            pointsNum = 0;
        }
        Paint = false;
    }
}

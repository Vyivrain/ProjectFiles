#include "mypaint.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyPaint w;
    w.show();


    return a.exec();
}

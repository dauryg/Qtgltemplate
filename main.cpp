#include <QtGui/QApplication>
#include "GlCanvas.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGLFormat format;
    format.setVersion( 3, 1);
    format.setDoubleBuffer( true );
    QGLFormat::setDefaultFormat( format );
    GlCanvas canvas;
    canvas.show();

    return a.exec();
}

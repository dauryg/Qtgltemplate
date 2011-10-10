#include <QtGui/QApplication>
#include "GlCanvas.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GlCanvas canvas;
    canvas.show();

    return a.exec();
}

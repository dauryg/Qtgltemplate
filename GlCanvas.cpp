#include "GlCanvas.h"
#include <iostream>

GlCanvas::GlCanvas(QWidget *parent)
    : QGLWidget(parent)
{
}

GlCanvas::~GlCanvas()
{

}

void GlCanvas::initVBO()
{

}

void GlCanvas::initShaders()
{

}

void GlCanvas::initGlew()
{
    GLenum err	= glewInit();

    if( err != GLEW_OK )
    {
        std::cerr << "Status: Using GLEW "<< glewGetErrorString(GLEW_VERSION_3_3)<< std::endl;
    }
}

void GlCanvas::initializeGL()
{
    initGlew();
    initShaders();
    initVBO();
}

void GlCanvas::resizeGL( int width, int height )
{
   glViewport( 0, 0, width, height);
}

void GlCanvas::paintGL()
{

}

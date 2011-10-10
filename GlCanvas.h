#ifndef GLCANVAS_H
#define GLCANVAS_H

#include "GL/glew.h"
#include <QGLWidget>

class GlCanvas: public QGLWidget
{
    Q_OBJECT

    private:
        GLuint vboHandle, programHandle, vertHandle, fragHandle;
        bool forwardCompatible;
        void initVBO();
        void initShaders();
        void initGlew();

    public:
        GlCanvas(QWidget *parent = 0);
        ~GlCanvas();
        void initializeGL();
        void resizeGL( int width, int height );
        void paintGL();
};

#endif // GLCANVAS_H

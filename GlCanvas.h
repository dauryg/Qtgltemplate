/*
Copyright (c) 2011 Daury Guzman <dauryguzman [] gmail com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the
following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO
EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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

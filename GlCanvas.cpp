/*
Copyright (c) 2011 Daury Guzman <daury@dauryguzman.com>

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

#include "GlCanvas.h"
#include <QtOpenGL>
#include <iostream>
#include <QDebug>

GlCanvas::GlCanvas(QWidget *parent)
    : QGLWidget(parent),vboHandle(0),vertHandle(0),fragHandle(0),programHandle(0),forwardCompatible(false)
{
    QDesktopWidget *desktop = QApplication::desktop();
    setFixedSize(640,480);
    setGeometry( QStyle::alignedRect( Qt::LeftToRight, Qt::AlignCenter, size(), desktop->availableGeometry()) );
    QTimer	*timer = new QTimer( this );
    connect(timer,SIGNAL( timeout() ),this,SLOT(updateGL()));
    timer->start();
}

GlCanvas::~GlCanvas()
{
    glDeleteShader( vertHandle );
    glDeleteShader( fragHandle );
    glDeleteProgram( programHandle );
    glDeleteBuffers( 1, &vboHandle);
}

void GlCanvas::initVBO()
{
    GLfloat vertices[] = {  0.0f,  0.5f, 0.0f,
                           -0.5f, -0.5f, 0.0f,
                            0.5f, -0.5f, 0.0f };

    GLfloat colors[] = {  0.5f,  0.0f, 0.0f,
                          0.0f,  0.5f, 0.0f,
                          0.0f,  0.0f, 0.5f};

    glGenBuffers(1, &vboHandle );
    glBindBuffer( GL_ARRAY_BUFFER, vboHandle );
    glBufferData( GL_ARRAY_BUFFER, sizeof(GLfloat) * 18, NULL, GL_STATIC_DRAW);
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 9, vertices);
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(GLfloat) * 9, sizeof(GLfloat) * 9, colors);
}

void GlCanvas::initShaders()
{
    programHandle	= glCreateProgram();
    vertHandle		= glCreateShader( GL_VERTEX_SHADER );
    fragHandle		= glCreateShader( GL_FRAGMENT_SHADER );

    QFile vert;

    if( forwardCompatible)
        vert.setFileName(":/forward.vert");
    else
        vert.setFileName(":/simple.vert");
    GLint status = 0;

    if( vert.exists() )
    {
        //read in
        vert.open( QFile::ReadOnly );
        QTextStream stream( &vert );

        QByteArray r;
        stream.reset();
        r.append(stream.readAll());

        const char *vertSource = r.constData();
        const char **source = &vertSource;

        //Send shader source
        glShaderSource( vertHandle, 1, source, NULL );

        //Compile
        glCompileShader( vertHandle );

        glGetShaderiv( vertHandle, GL_COMPILE_STATUS, &status);

        if( !status)
        {
            GLint length = 0;
            glGetShaderiv( vertHandle, GL_INFO_LOG_LENGTH, &length);
            GLchar *info = new GLchar[length];
            glGetShaderInfoLog( vertHandle, length, NULL, info);
            qDebug() << info;
            delete[] info;

        }

        //attach shader
        glAttachShader( programHandle, vertHandle );

        status = 0;
    }
    else
    {
        qDebug() << "Vertex Shader Source Not Found";
    }

    QFile frag;

    if( forwardCompatible)
        frag.setFileName(":/forward.frag");
    else
        frag.setFileName(":/simple.frag");

    if( frag.exists() )
    {
        //read in
        frag.open( QFile::ReadOnly );
        QTextStream stream( &frag );
        QByteArray r;
        stream.reset();
        r.append(stream.readAll());
        const char *fragSource = r.constData();
        const char **source = &fragSource;

        //Send shader source
        glShaderSource( fragHandle, 1, source, NULL );

        //Compile
        glCompileShader( fragHandle );

        //Get Compile Status
        glGetShaderiv( fragHandle, GL_COMPILE_STATUS, &status);

        if( !status)
        {
            GLint length = 0;
            glGetShaderiv( vertHandle, GL_INFO_LOG_LENGTH, &length);
            GLchar *info = new GLchar[length];
            glGetShaderInfoLog( vertHandle, length, NULL, info);
            qDebug() << info;
            delete[] info;
        }

        //attach shader
        glAttachShader( programHandle, fragHandle );

        if( forwardCompatible )
        {
            glBindFragDataLocation( fragHandle, 0, "fragColor");
        }

        status = 0;
    }
    else
    {
        qDebug() << "Fragment Shader Source Not Found";
    }

    glBindAttribLocation ( programHandle, 0, "vertPosition" );
    glBindAttribLocation ( programHandle, 1, "mycolor" );
    glLinkProgram( programHandle );

    glGetShaderiv( programHandle, GL_LINK_STATUS, &status);
    if( !status)
    {
        GLint length = 0;
        glGetProgramiv( programHandle, GL_INFO_LOG_LENGTH, &length);
        GLchar *info = new GLchar[length];
        glGetProgramInfoLog( programHandle, length, NULL, info);
        qDebug() << info;
        delete[] info;
    }

    glUseProgram( programHandle );
}

void GlCanvas::initGlew()
{
    GLenum err	= glewInit();

    if( err != GLEW_OK )
    {
        qDebug() << "Status: Using GLEW "<< glewGetErrorString( err );
    }

    if( GLEW_VERSION_3_1 )
    {
        forwardCompatible = true;
    }
  }

void GlCanvas::initializeGL()
{
    initGlew();
    initShaders();
    initVBO();
    glClearColor( 0.5f, 0.5f, 0.5f, 1.0f );
}

void GlCanvas::resizeGL( int width, int height )
{
   glViewport( 0, 0, width, height);
}

void GlCanvas::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT );
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, (char *)(sizeof(GLfloat)*9) );
    glDrawArrays( GL_TRIANGLES, 0, 3);
    glFlush();
}

#-------------------------------------------------
#
# Project created by QtCreator 2011-10-10T00:52:39
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = qtgltemplate
TEMPLATE = app


SOURCES += main.cpp \
    GlCanvas.cpp \
    glew.c

HEADERS  += \
    GlCanvas.h \
    GL/wglew.h \
    GL/glxew.h \
    GL/glew.h

OTHER_FILES += \
    shaders/simple.vert \
    shaders/simple.frag

RESOURCES += \
    shaders.qrc












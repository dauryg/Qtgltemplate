
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
    shaders/simple.frag \
    shaders/forward.vert \
    shaders/forward.frag

RESOURCES += \
    shaders.qrc



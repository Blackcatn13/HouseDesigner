QT += core \
    gui \
    opengl
unix:!macx:LIBS += -lglut \
    -lGLEW \
    -lGLU
win32:LIBS += "C:\Archivos de programa\Microsoft SDKs\Windows\v6.1\Lib\glew32.lib"
macx:LIBS += -framework \
    GLUT
TARGET = Thoth
TEMPLATE = app
SOURCES += main.cpp \
    thothwindow.cpp \
    Model.cpp \
    GLWidget.cpp \
    Camera.cpp \
    Illumination.cpp
HEADERS += thothwindow.h \
    Util.h \
    Model.h \
    GLWidget.h \
    Camera.h \
    Illumination.h
FORMS += thothwindow.ui
OTHER_FILES += simple.vert \
    simple.frag

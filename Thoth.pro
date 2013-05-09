QT += core \
    gui \
    opengl
unix:!macx:LIBS += -lglut \
    -lGLEW \
    -lGLU \
    -lassimp
macx:LIBS += -framework \
    GLUT
TARGET = Thoth
TEMPLATE = app
SOURCES += Camera.cpp \
    GLWidget.cpp \
    Illumination.cpp \
    main.cpp \
    Model.cpp \
    ModelManager.cpp \
    Point3D.cpp \
    Render.cpp \
    Render2D.cpp \
    Scenary.cpp \
    thothwindow.cpp \
    RenderManager.cpp \
    CameraManager.cpp \
    CameraOrtho.cpp \
    CameraPerspective.cpp \
    ProjectManager.cpp \
    TreeFile.cpp \
    RenderExplorer.cpp \
    CameraFP.cpp \
    TextureManager.cpp \
    Texture.cpp
HEADERS += Camera.h \
    GLWidget.h \
    Illumination.h \
    Model.h \
    ModelManager.h \
    Point3D.h \
    Render.h \
    Render2D.h \
    Scenary.h \
    thotwindow.h \
    Util.h \ 
    RenderManager.h \
    thothwindow.h \
    CameraManager.h \
    CameraOrtho.h \
    CameraPerspective.h \
    ProjectManager.h \
    TreeFile.h \
    RenderExplorer.h \
    CameraFP.h \
    TextureManager.h \
    Texture.h
FORMS += thothwindow.ui
OTHER_FILES += simple.vert \
    simple.frag

#include <QtGui/QMouseEvent>
#include "GLWidget.h"
#include <QApplication>
#include "Scenary.h"
#include "Render2D.h"

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
    setMouseTracking(true);
    actualMode = EDITOR_2D;
}

GLWidget::~GLWidget()
{
    // TODO: 
    // Esborrar els valors del renderMap abans de sortir de l'aplicació
}

/*****************************************************************************
 * initializeGL()
 *      Called at context creation. Sets initial state.
 *****************************************************************************/
void GLWidget::initializeGL()
{

#ifndef __APPLE__

    // 0) OpenGL 2.0 support test
    //    (needed for shading)
    //----------------------------------------------------------

    glewInit();

    if (glewIsSupported("GL_VERSION_2_0"))
    {
        qDebug() << "Ready for OpenGL 2.0";
    }
    else
    {
        qDebug() << "OpenGL 2.0 not supported";
        QApplication::exit(-1);
    }

#endif


    // 1) Go for a well known initialization state.
    //    (essential stuff only)
    //----------------------------------------------------------

    // 1a) Setting default values to clean buffers
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClearDepth(1.0f); // This is the default OpenGL value, but I'm making it explicit for you

    // 1b) Backface culling enabled
    //     (this will speedup rendering)
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // 1c) Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    // 2) Initi our render modes
    // Default is Editor_2D
    initializeRenderMap();

}

/*****************************************************************************
 * resizeGL()
 *      Called at context resizing. Controls aspect ratio changes.
 *****************************************************************************/
void GLWidget::resizeGL(int w, int h)
{
    // Resize all the render Modes cameras.
    RenderMapIterator it = renderModes.begin();
    for(; it != renderModes.end(); ++it)
    {
        it->second->SetCameraProjection(w,h);
    }
}

/*****************************************************************************
 * paintGL()
 *      Called to draw the actual render mode scene.
 *****************************************************************************/
void GLWidget::paintGL()
{

    // Clean buffers:
    // COLOR to ensure final representation has no waste from previous renders
    // DEPTH to ensure correct representation of objects given the depht testing used
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // Call the draw function of the actual render Mode.
    RenderMapIterator it = renderModes.find(actualMode);
    if(it != renderModes.end())
    {
        it->second->Draw();
    }
}

/*****************************************************************************
 * mousePressEvent()
 *      Called on mouse click. Controls this input.
 *****************************************************************************/
void GLWidget::mousePressEvent(QMouseEvent *event)
{

    // Crear funcio per fer parets
    /*if (event->buttons() & Qt::LeftButton)
    {
        posCam.x = event->x();
        posCam.y = event->y();
    }*/

}


/*****************************************************************************
 * resizeGL()
 *      Called on mouse move. Controls this input.
 *****************************************************************************/
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{

    // moure per crear parets
   /* bool update = false;

    if (event->buttons() & Qt::LeftButton)
    {
        camera->move(	posCam.x - event->x(),
            posCam.y - event->y());

        posCam.x = event->x();
        posCam.y = event->y();

        update = true;
    }

    if(update)
        updateGL();
        */
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    RenderMapIterator it = renderModes.find(actualMode);
    if(it != renderModes.end())
    {
        if(event->delta() > 0)
            it->second->AddCameraDistance(0.5);
        else
            it->second->AddCameraDistance(-0.5);
    }
    updateGL();
}

/*****************************************************************************
 * resizeGL()
 *      Called on keystrokes. Controls this input.
 *****************************************************************************/
void GLWidget::keyPressEvent(QKeyEvent* event)
{

    bool update = false;

    // Call the actual render mode key update to make its changes.
    RenderMapIterator it = renderModes.find(actualMode);
    if(it != renderModes.end())
    {
        update = it->second->KeyEvent(event->key());
    }
    
    if(update)
        updateGL();

}

void GLWidget::initializeRenderMap()
{
    renderModes = RenderMap();
    renderModes.insert(std::pair<Modes, Render*>(EDITOR_2D, new Render2D()));
    // TODO:
    // Afegir els inserts per els renders que falten un cop creats.

    // Resize all the render modes camera.
    RenderMapIterator it = renderModes.begin();
    for(; it != renderModes.end(); ++it)
    {
        it->second->SetCameraProjection(size().width(), size().height());
    }
}

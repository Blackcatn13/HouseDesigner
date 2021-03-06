#include <QtGui/QMouseEvent>
#include "GLWidget.h"
#include <QApplication>
#include "Scenary.h"
#include "Render2D.h"
#include "RenderManager.h"
#include "CameraManager.h"
#include "Shadermanager.h"
#include "ModelManager.h"

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
    setMouseTracking(true);
    actualMode = EDITOR_2D;
    cursor = Qt::ArrowCursor;
    connect(this, SIGNAL(setMouseMove(bool)), RenderManager::GetInstance()->GetRenderMode(EXPLORER), SLOT(setMouseMove(bool)));
}

GLWidget::~GLWidget()
{
    CScenary::getInstance()->CleanUp();
    RenderManager::GetInstance()->CleanUp();
    CShaderManager::GetInstance()->CleanUp();
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
    glClearColor(0.2f, 0.2f, 0.8f, 1.0f);
    glClearDepth(1.0f); // This is the default OpenGL value, but I'm making it explicit for you

    // 1b) Backface culling enabled
    //     (this will speedup rendering)
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // 1c) Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    CShaderManager::GetInstance()->initShaders(this->context(), SIMPLE);
    RenderManager::GetInstance()->GetRenderMode(EDITOR_2D)->SetCameraProjection(INIT_WIDTH, INIT_HEIGHT);

}

/*****************************************************************************
 * resizeGL()
 *      Called at context resizing. Controls aspect ratio changes.
 *****************************************************************************/
void GLWidget::resizeGL(int w, int h)
{
    // Resize all the render Modes cameras.
    width = w;
    heigth = h;
    RenderManager* RM = RenderManager::GetInstance();
    RM->SetProjection(w, h, actualMode);
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
    RenderManager* RM = RenderManager::GetInstance();
    /*switch (actualMode)
    {
    case EXPLORER:
    case EXPLORER_ISO:
        setCursor(Qt::CrossCursor);
        break;
    case EDITOR_2D:
        setCursor(Qt::ArrowCursor);
    }*/
    setCursor(cursor);
    RM->GetRenderMode(actualMode)->Draw();

}

/*****************************************************************************
 * mousePressEvent()
 *      Called on mouse click. Controls this input.
 *****************************************************************************/
void GLWidget::mousePressEvent(QMouseEvent *event)
{
    RenderManager* RM = RenderManager::GetInstance();
    RM->GetRenderMode(actualMode)->mousePressEvent(event);
    //updateGL();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    RenderManager* RM = RenderManager::GetInstance();
    RM->GetRenderMode(actualMode)->mouseReleaseEvent(event);
    //updateGL();
}


/*****************************************************************************
 * resizeGL()
 *      Called on mouse move. Controls this input.
 *****************************************************************************/
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    RenderManager* RM = RenderManager::GetInstance();
    RM->GetRenderMode(actualMode)->mouseMoveEvent(event, mapToGlobal(QPoint(width/2, heigth/2)).x(), mapToGlobal(QPoint(width/2, heigth/2)).y());
    //updateGL();
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    RenderManager* RM = RenderManager::GetInstance();
    if(event->delta() > 0)
        RM->GetRenderMode(actualMode)->AddCameraDistance(0.5);
    else
        RM->GetRenderMode(actualMode)->AddCameraDistance(-0.5);
    //updateGL();
}

/*****************************************************************************
 * resizeGL()
 *      Called on keystrokes. Controls this input.
 *****************************************************************************/
void GLWidget::keyPressEvent(QKeyEvent* event)
{
    RenderManager* RM = RenderManager::GetInstance();
    CameraManager *cm = CameraManager::GetInstance();
    if(event->key() == Qt::Key_L)
    {
        actualMode = EXPLORER;
        cm->setCurrentCamera(FP);
        RM->GetRenderMode(actualMode)->SetCameraProjection(width, heigth);
        cursor = Qt::CrossCursor;
        emit setMouseMove(true);
        CShaderManager::GetInstance()->setShader(TEXTURE);
    }
    else if(event->key() == Qt::Key_P)
    {
        CShaderManager::GetInstance()->setShader(SIMPLE);
        actualMode = EDITOR_2D;
        cm->setCurrentCamera(ORTHOGONAL);
        RM->GetRenderMode(actualMode)->SetCameraProjection(width, heigth);
        cursor = Qt::ArrowCursor;
    }
    else if(event->key() == Qt::Key_C)
    {
        CScenary::getInstance()->ClearFloor();
    }
    else
    {
        // Call the actual render mode key update to make its changes.
        RM->GetRenderMode(actualMode)->KeyEvent(event->key());
    }

    //updateGL();
}

void GLWidget::changeCursor(Qt::CursorShape cur)
{
    cursor = cur;
}

void GLWidget::enterEvent(QEvent *event)
{
    if(actualMode == EXPLORER)
    {
        emit setMouseMove(true);
        cursor = Qt::CrossCursor;
        this->setFocus();
    }
}
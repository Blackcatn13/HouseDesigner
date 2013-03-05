#include <QtGui/QMouseEvent>
#include "GLWidget.h"
#include <QApplication>

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
    setMouseTracking(true);
}

GLWidget::~GLWidget()
{
    if (camera)
        delete camera;
    if (illum)
        delete illum;
    if (model)
        delete model;
    if (shader)
        delete shader;
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

    // 2) Init our own architecture (camera, lights, action!)
    //----------------------------------------------------------
    camera = new Camera();
    illum = new Illumination();
    model = new Model();


    // 3) Init shaders
    //----------------------------------------------------------
    //shader =    new QGLShaderProgram();
    //initializeShaders(QString("gouraud"));
}

/*****************************************************************************
 * resizeGL()
 *      Called at context resizing. Controls aspect ratio changes.
 *****************************************************************************/
void GLWidget::resizeGL(int w, int h)
{

    camera->setProjection(w,h);
}

/*****************************************************************************
 * resizeGL()
 *      Called automatically after init, on possible clock events,
 *      or after UpdateGL requests. Controls context painting.
 *****************************************************************************/
void GLWidget::paintGL()
{

    // Clean buffers:
    // COLOR to ensure final representation has no waste from previous renders
    // DEPTH to ensure correct representation of objects given the depht testing used
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    if(camera->getView() == PERSPECTIVE)
    {
        camera->setProjection(size().width(), size().height());
        renderScene();
    }
    else
    {
        for(int i = 0; i < 4; i++)
        {
            camera->setProjection(size().width(), size().height(), i);
            renderScene(i);
        }
    }
}

/*****************************************************************************
 * resizeGL()
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
    /*qDebug() << event->delta();
    if (event->delta() > 0)
        model ->zoomIn();
    else
        model->zoomOut();
    updateGL();*/
}

/*****************************************************************************
 * resizeGL()
 *      Called on keystrokes. Controls this input.
 *****************************************************************************/
void GLWidget::keyPressEvent(QKeyEvent* event)
{

    /*bool update = true;

    switch(event->key()) {
    case Qt::Key_W:
        illum->move(-0.2,0.0);
        break;
    case Qt::Key_S:
        illum->move(0.2,0.0);
        break;
    case Qt::Key_A:
        illum->move(0.0,-0.2);
        break;
    case Qt::Key_D:
        illum->move(0.0,0.2);
        break;
    case Qt::Key_P:
        shader->bind();
        break;
    case Qt::Key_O:
        shader->release();
        break;
    default:
        update = false;
    }

    if(update)
        updateGL();*/

}

/*****************************************************************************
 * initializeShaders()
 *      Loads custom shader by specifying filename (expects frag/vert pair)
 *****************************************************************************/
void GLWidget::initializeShaders(QString filename)
{

    bool result;
    result = shader->addShaderFromSourceFile( QGLShader::Vertex, filename + ".vert" );
    if ( !result )
        qDebug() << "Vertex: " << shader->log();
    else
        qDebug() << "Vertex shader works!";
    result = shader->addShaderFromSourceFile( QGLShader::Fragment, filename + ".frag" );
    if ( !result )
        qDebug() << "Fragment: " << shader->log();
    else
        qDebug() << "Fragment shader works!";
    result = shader->link();
    if ( !result )
        qDebug() << "Link: " << shader->log();
    else
        qDebug() << "Shaders link: OK!";
    result = shader->bind();
    if ( !result )
        qDebug() << "Bind: " << shader->log();
    else
        qDebug() << "Shaders bind: OK!";

}

/*****************************************************************************
 * releaseAllShaders()
 *      Unload shaders, return to OpenGL fixed function.
 *****************************************************************************/
void GLWidget::releaseAllShaders()
{

    shader->release();
    shader->removeAllShaders();

}

/*****************************************************************************
 * resizeGL()
 *      Called automatically after init, on possible clock events,
 *      or after UpdateGL requests. Controls context painting.
 *****************************************************************************/
void GLWidget::usePerspective()
{
    camera->setView(PERSPECTIVE);
    updateGL();
    this->setFocus();
}

/*****************************************************************************
 * resizeGL()
 *      Called automatically after init, on possible clock events,
 *      or after UpdateGL requests. Controls context painting.
 *****************************************************************************/
void GLWidget::useMultiview()
{
    camera->setView(MULTIVIEW);
    updateGL();
    this->setFocus();
}

/*****************************************************************************
 * resizeGL()
 *      Called automatically after init, on possible clock events,
 *      or after UpdateGL requests. Controls context painting.
 *****************************************************************************/
void GLWidget::renderScene(int camera_index)
{
    // Update light with its current position
    illum->update();
    // Update camera to its current position
    camera->update(camera_index);

    // Draw the coordinate axis to ease user comprehension of the scene
    model->Eixos();
    // Draw an sphere representing light position (user interaction purpose)
    illum->draw();

    // Draw sample model
    model->Dibuixa2();

}

#ifndef _GLWIDGET_H
#define _GLWIDGET_H

#include "Util.h"
#include <QtOpenGL/QGLWidget>
#include <QGLShaderProgram>
#include "ModelManager.h"
#include "Camera.h"
#include "Illumination.h"

class GLWidget : public QGLWidget {

    Q_OBJECT // must include this if you use Qt signals/slots

public:
    GLWidget(QWidget *parent = NULL);
    ~GLWidget();

public slots:
    void usePerspective();
    void useMultiview();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    QGLShaderProgram *shader;
    Camera *camera;
    Illumination *illum;

    Point2D posCam;
    bool texture;
    bool shaders;

    void initializeShaders(QString filename);
    void releaseAllShaders();
    void renderScene(int camera_index=0);
};

#endif  /* _GLWIDGET_H */

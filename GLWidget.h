#ifndef _GLWIDGET_H
#define _GLWIDGET_H

#include "Util.h"
#include <QtOpenGL/QGLWidget>
#include "Render.h"

class GLWidget : public QGLWidget {

    Q_OBJECT // must include this if you use Qt signals/slots

public:
    GLWidget(QWidget *parent = NULL);
    ~GLWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Modes actualMode;
    float width;
    float heigth;
};

#endif  /* _GLWIDGET_H */

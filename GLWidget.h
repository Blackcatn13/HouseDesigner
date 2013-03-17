#ifndef _GLWIDGET_H
#define _GLWIDGET_H

#include "Util.h"
#include <QtOpenGL/QGLWidget>
#include "Render.h"
#include <map>

typedef std::map<Modes, Render*> RenderMap;
typedef std::map<Modes, Render*>::iterator RenderMapIterator;

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

private:

    RenderMap renderModes;
    Modes actualMode;

    void initializeRenderMap();
};

#endif  /* _GLWIDGET_H */

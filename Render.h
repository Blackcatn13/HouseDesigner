#ifndef RENDER_H
#define RENDER_H

#include "Util.h"
#include <QMouseEvent>
#include <qobject.h>

class Render : public QObject
{
    Q_OBJECT
public:
    void virtual Draw() = 0;
    void virtual Update() = 0;
    bool virtual KeyEvent(int key) = 0;
    void virtual SetCameraProjection(int w, int h) = 0;
    void virtual AddCameraDistance(float d) = 0;
    void virtual mousePressEvent(QMouseEvent *event) = 0;
    void virtual mouseReleaseEvent(QMouseEvent *event) = 0;
    void virtual mouseMoveEvent(QMouseEvent *event, int x, int y) = 0;
    Render(QObject* p = 0);
    ~Render();
};

#endif
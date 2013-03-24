#ifndef RENDER2D_H
#define RENDER2D_H

#include "Util.h"
#include "Render.h"

class Camera;

class Render2D : public Render
{
public:
    Render2D();
    ~Render2D();
    void Draw();
    void Update();
    bool KeyEvent(int key);
    void SetCameraProjection(int w, int h);
    void AddCameraDistance(float d);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    Camera *camera;
};

#endif
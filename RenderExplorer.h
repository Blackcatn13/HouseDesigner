#ifndef RENDEREXPLORER_H
#define RENDEREXPLORER_H

#include "Util.h"
#include "Render.h"

#define ASPECT_RATIO (4/3)
class Camera;

class RenderExplorer : public Render
{
public:
    RenderExplorer();
    ~RenderExplorer();
    void Draw();
    void Update();
    bool KeyEvent(int key);
    void SetCameraProjection(int w, int h);
    void AddCameraDistance(float d);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event, int x, int y);
private:
    Camera *camera;
    int gridX;
    int gridY;
    bool fly;
    float width, heigth;
    Point2D mousePosition;
    bool clicked;
    ModelInfo selectedModel;
    int selectedPosition;
    void getWorldMouseCoord(int x, int y, float &wx, float &wy, float &wz);
};

#endif

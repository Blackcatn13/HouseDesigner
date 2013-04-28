#ifndef RenderIso_H
#define RenderIso_H

#include "Util.h"
#include "Render.h"

#define ASPECT_RATIO (4/3)
#define SIN_45 0.707106781
class Camera;

class RenderIso : public Render
{
public:
    RenderIso();
    ~RenderIso();
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
    int gridX;
    int gridY;
    Point2D firstClick;
    Point2D firstTile;
    Point2D secondTile;
    Point2D vecDir;
    Point2D actPos;
    float xRot, yRot, zRot;
    QPoint lastPos;
    bool clicked;
    void getWorldMouseCoord(int x, int y, float &wx, float &wz);
    void DrawLine();
    void DrawQuad();
    void MoveQuad(float wx, float wz);
    void MoveLine(float wx, float wz);
    void AddObject();
    void AddWall();
    void FirstClickWall(float wx, float wz);
    void FirstClickObject(float wx, float wz);
};

#endif

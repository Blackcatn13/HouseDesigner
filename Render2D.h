#ifndef RENDER2D_H
#define RENDER2D_H

#include "Util.h"
#include "Render.h"

#define ASPECT_RATIO (4/3)
#define SIN_45 0.707106781
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
    void mouseMoveEvent(QMouseEvent *event, int x, int y);
    void setEditMode(EditModes em);
    EditModes getActualEditMode() {return actualEditMode;}
private:
    Camera *camera;
    int gridX;
    int gridY;
    Point2D firstClick;
    Point2D firstTile;
    Point2D secondTile;
    Point2D vecDir;
    Point2D actPos;
    bool clicked;
    void getWorldMouseCoord(int x, int y, float &wx, float &wz);
    void DrawLine();
    void DrawQuad();
    void MoveQuad(float wx, float wz);
    void MoveQuadStair(float wx, float wz);
    void MoveLine(float wx, float wz);
    void AddObject();
    void AddWall();
    void AddStair();
    void FirstClickWall(float wx, float wz);
    void FirstClickObject(float wx, float wz);
    void FirstClickStair(float wx, float wz);
    EditModes actualEditMode;
};

#endif
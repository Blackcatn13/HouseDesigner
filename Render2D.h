#ifndef RENDER2D_H
#define RENDER2D_H

#include "Util.h"
#include "Render.h"

#define ASPECT_RATIO (4/3)
#define SIN_45 0.707106781
class Camera;

class Render2D : public Render
{
    Q_OBJECT
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
    int rotation;
    bool clicked;
    void getWorldMouseCoord(int x, int y, float &wx, float &wz);
    void DrawLine();
    void DrawQuad();
    void DrawInverseQuad();
    void DrawInverseQuad1();
    void MoveQuad(float wx, float wz);
    void RefreshQuad();
    void RefreshQuadStair();
    void MoveQuadStair(float wx, float wz);
    void MoveLine(float wx, float wz);
    void AddObject();
    void AddWall();
    void AddStair();
    void FirstClickWall(float wx, float wz);
    void FirstClickObject(float wx, float wz);
    void FirstClickStair(float wx, float wz);
    EditModes actualEditMode;
    ModelInfo selectedModel;
    int selectedPosition;
signals:
    void changedMode(string mode);
    void pickedInfo(string);
    void setMessage(string, int);
};

#endif
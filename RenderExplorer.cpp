#include "RenderExplorer.h"
#include "Scenary.h"
#include "CameraManager.h"
#include "Camera.h"
#include <qcursor.h>
#include <qwidget.h>
#include "Shadermanager.h"

RenderExplorer::RenderExplorer()
{
    camera = CameraManager::GetInstance()->GetCamera(FP);
    fly = false;
    mouseMove = true;
}

RenderExplorer::~RenderExplorer()
{
    if(camera)
        delete camera;
}

void RenderExplorer::Draw()
{
    camera->update();
    CScenary * scene = CScenary::getInstance();
    scene->DrawAxis();
    scene->DrawGrid();
    scene->DrawStairs();
    scene->Draw();
    scene->DrawFloor();
    scene->DrawCeil(); 
}

void RenderExplorer::Update()
{
}

bool RenderExplorer::KeyEvent(int key)
{
    bool update = true;
    Point2D move;
    move.x = 0;
    move.y = 0;
    switch(key)
    {
    case Qt::Key_A:
        move.y += 0.25;
        break;
    case Qt::Key_S:
        move.x -= 0.25;
        break;
    case Qt::Key_D:
        move.y -= 0.25;
        break;
    case Qt::Key_W:
        move.x += 0.25;
        break;
    case Qt::Key_Space:
        fly = !fly;
        break;
    case Qt::Key_PageDown:
    case Qt::Key_Down:
    case Qt::Key_Minus:
        {
            int floor = CScenary::getInstance()->getCurrentFloor();
            if(floor > 0)
            {
                CScenary::getInstance()->ChangeFloor(floor - 1);
                camera->AddDistance(-FLOOR_HEIGHT);
            }
            break;
        }
    case Qt::Key_PageUp:
    case Qt::Key_Up:
    case Qt::Key_Plus:
        {
            int floor = CScenary::getInstance()->getCurrentFloor();
            if(floor < CScenary::getMaxFloors() - 1)
            {
                CScenary::getInstance()->ChangeFloor(floor + 1);
                camera->AddDistance(FLOOR_HEIGHT);
            }

            break;
        }
    default:
        update = false;
    }
    camera->move(move.x, move.y, fly);
    return update;
}

void RenderExplorer::SetCameraProjection(int w, int h)
{
    camera->setProjection(w, h);
    width = w;
    heigth = h;
    camera->update();
}

void RenderExplorer::AddCameraDistance(float)
{
}

void RenderExplorer::mousePressEvent(QMouseEvent *event)
{
    float WX;
    float WY;
    float WZ;
    getWorldMouseCoord(event->x(),event->y(), WX, WY, WZ);
    size_t indx;
    ModelInfo pickedModel = CScenary::getInstance()->getPickedObject3D(WX, WY, WZ, indx);
    if (indx != -1)
    {
        selectedModel = pickedModel;
        selectedPosition = indx;
        emit changeTab();
        emit pickedInfo("Picked " + selectedModel.textureName.ObjectName);
    }
}

void RenderExplorer::mouseReleaseEvent(QMouseEvent *event)
{

}

void RenderExplorer::mouseMoveEvent(QMouseEvent *event, int x, int y)
{
    
    float yaw, pitch;
    if(mouseMove)
    {
        Point2D mousePos(event->pos().x(), event->pos().y());

        Point2D mouseRelPos(mousePos.x - width/2, mousePos.y - heigth/2);
        yaw = mouseRelPos.x *0.1;
        pitch = -mouseRelPos.y * 0.1;
        camera->AddYawAndPitch(yaw, pitch);

        QCursor::setPos(QPoint(x,y));
    }
}

void RenderExplorer::getWorldMouseCoord(int x, int y, float &wx, float &wy, float &wz)
{
    GLfloat MWX=0.0, MWY=0.0, MWZ=0.0;
    GLdouble rx=0.0, ry=0.0, rz=0.0;

    GLdouble modelview[16];
    GLdouble projection[16];
    GLint viewport[4];

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    MWX = (float)x;
    MWY = (float)viewport[3] - (float)y;
    glReadPixels(x, int(MWY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &MWZ);
    gluUnProject(MWX, MWY, MWZ, modelview, projection, viewport, &rx, &ry, &rz);
    wx = rx;
    wy = ry;
    wz = rz;
}

void RenderExplorer::setMouseMove(bool m)
{
    mouseMove = m;
}

void RenderExplorer::changeModelTexture(ModelInfo mi, int pos)
{
    switch(pos)
    {
    case 1:
        selectedModel.textureName.color.c1 = mi.textureName.color.c1;
        selectedModel.textureName.material.M1 = mi.textureName.material.M1;
        break;
    case 2:
        selectedModel.textureName.color.c2 = mi.textureName.color.c2;
        selectedModel.textureName.material.M2 = mi.textureName.material.M2;
        break;
    case 3:
        selectedModel.textureName.color.c3 = mi.textureName.color.c3;
        selectedModel.textureName.material.M3 = mi.textureName.material.M3;
        break;
    case 4:
        selectedModel.textureName.color.c4 = mi.textureName.color.c4;
        selectedModel.textureName.material.M4 = mi.textureName.material.M4;
        break;
    }
    CScenary::getInstance()->ChangeModelInfo(selectedModel, selectedPosition);
}

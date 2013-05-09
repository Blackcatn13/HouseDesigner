#include "RenderExplorer.h"
#include "Scenary.h"
#include "CameraManager.h"
#include "Camera.h"
#include <qcursor.h>
#include <qwidget.h>

RenderExplorer::RenderExplorer()
{
    camera = CameraManager::GetInstance()->GetCamera(FP);
    fly = false;
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
        {
            int floor = CScenary::getInstance()->getCurrentFloor();
            if(floor > 0)
                CScenary::getInstance()->ChangeFloor(floor - 1);
            break;
        }
    case Qt::Key_PageUp:
        {
            int floor = CScenary::getInstance()->getCurrentFloor();
            if(floor < CScenary::getMaxFloors() - 1)
                CScenary::getInstance()->ChangeFloor(floor + 1);
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

void RenderExplorer::mousePressEvent(QMouseEvent*)
{

}

void RenderExplorer::mouseReleaseEvent(QMouseEvent*)
{

}

void RenderExplorer::mouseMoveEvent(QMouseEvent *event, int x, int y)
{
    float yaw, pitch;
    Point2D mousePos(event->pos().x(), event->pos().y());

    Point2D mouseRelPos(mousePos.x - width/2, mousePos.y - heigth/2);
    yaw = mouseRelPos.x *0.1;
    pitch = -mouseRelPos.y * 0.1;
    camera->AddYawAndPitch(yaw, pitch);

    QCursor::setPos(QPoint(x,y));
}

void RenderExplorer::getWorldMouseCoord(int x, int y, float &wx, float &wz)
{
    GLfloat MWX, MWY;
    GLdouble rx, ry, rz;

    GLdouble modelview[16];
    GLdouble projection[16];
    GLint viewport[4];

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    MWX = (float)x;
    MWY = (float)viewport[3] - (float)y;

    gluUnProject(MWX, MWY, 0, modelview, projection, viewport, &rx, &ry, &rz);
    wx = rx;
    wz = rz;
}
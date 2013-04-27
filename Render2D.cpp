#include "Render2D.h"
#include "Scenary.h"
#include "CameraManager.h"
#include "Camera.h"
#include "ModelManager.h"


Render2D::Render2D()
{
    camera = CameraManager::GetInstance()->GetCamera(ORTHOGONAL);
    clicked = false;
}

Render2D::~Render2D()
{
    if(camera)
        delete camera;
}

void Render2D::Draw()
{
    camera->update();
    CScenary * scene = CScenary::getInstance();
    scene->DrawAxis();
    scene->DrawGrid();
    scene->Draw();
    if(clicked)
    {
        Types t = scene->getActiveType();
        switch(t)
        {
        case WALL:
            {
                glLineWidth(5);
                glColor3f(1.0, 0.0, 1.0);
                glBegin(GL_LINES);
                    glVertex3f(firstTile.x, 0.05, firstTile.y);
                    glVertex3f(secondTile.x, 0.05, secondTile.y);
                glEnd();
                glLineWidth(1);
            }
        case OBJECT:
            {
                glColor3f(1.0, 0.2, 1.0);
                glBegin(GL_QUADS);
                    glVertex3f(firstTile.x, -0.005, firstTile.y);
                    glVertex3f(firstTile.x, -0.005, secondTile.y);
                    glVertex3f(secondTile.x, -0.005, secondTile.y);
                    glVertex3f(secondTile.x, -0.005, firstTile.y);
                glEnd();
            }
        }
    }
}

void Render2D::Update()
{

}

bool Render2D::KeyEvent(int key)
{
    bool update = true;

    switch(key)
    {
    case Qt::Key_A:
        camera->move(0.0,-0.6);
        gridX -= 0.6;
        break;
    case Qt::Key_S:
        camera->move(-0.6,0.0);
        gridY += 0.6;
        break;
    case Qt::Key_D:
        camera->move(0.0,0.6);
        gridX += 0.6;
        break;
    case Qt::Key_W:
        camera->move(0.6,0.0);
        gridY -= 0.6;
        break;
    default:
        update = false;
    }

    return update;
}

void Render2D::SetCameraProjection(int w, int h)
{
    camera->setProjection(w,h);
}

void Render2D::AddCameraDistance(float d)
{
    camera->AddDistance(d);
}

void Render2D::mousePressEvent(QMouseEvent *event)
{
    CScenary *scenary = CScenary::getInstance();
    Types t = scenary->getActiveType();
    int x = event->x();
    int y = event->y();
    float wx, wz;

    getWorldMouseCoord(x, y, wx, wz);

    switch(t)
    {
    case WALL:
        {
            if (wx > 0.0 && wz > 0.0)
            {
                int rtx = (int)(wx*2)/2.0 + 0.5;
                int rty = (int)(wz*2)/2.0 + 0.5;
    
                if(!clicked)
                {
                    firstClick.x = wx;
                    firstClick.y = wz;
                    firstTile.x = rtx;
                    firstTile.y = rty;
                    secondTile.x = rtx;
                    secondTile.y = rty;
                    clicked = true;
                }
            }
        }
    case OBJECT:
        {
            if (wx > 0.0 && wz > 0.0)
            {
                int rtx = (int)wx;
                int rty = (int)wz;
                if(!clicked)
                {
                    firstClick.x = wx;
                    firstClick.y = wz;
                    firstTile.x = rtx;
                    firstTile.y = rty;
                    CPoint3D max = CModelManager::GetInstance()->getModelSize(scenary->getActiveModel());
                    secondTile.x = rtx + max.x;
                    secondTile.y = rty + max.z;
                    clicked = true;
                }
            }
        }
    }

}

void Render2D::mouseReleaseEvent(QMouseEvent *event)
{
    if(clicked)
    {
        CScenary *scenary = CScenary::getInstance();
        Types t = scenary->getActiveType();
        ModelInfo ii;
        ii.modelName = scenary->getActiveModel();
        ii.scale = CPoint3D(1,1,1);
        ii.type = t;
        clicked = false;

        switch(t)
        {
        case WALL:
            { 
                int angle;
                int start, end;
                if(firstTile.x == secondTile.x)
                {
                    if(firstTile.y < secondTile.y)
                    {
                        start = firstTile.y;
                        end = secondTile.y;
                        angle = 180;
                    }
                    else
                    {
                        start = secondTile.y;
                        end = firstTile.y;
                        angle = 180;
                    }
                    ii.rotation = CPoint3D(0, 180, 0);
                    for(int i = start; i < end; i++)
                    {
                        ii.position = CPoint3D(firstTile.x - 0.05 , 0, i);
                        if(!scenary->getWallCollision(ii))
                            scenary->addModel(ii);
                    }
                }
                else
                {
                    if(firstTile.x < secondTile.x)
                    {
                        start = firstTile.x;
                        end = secondTile.x;
                        angle = 90;
                    }
                    else
                    {
                        start = secondTile.x;
                        end = firstTile.x;
                        angle = -90;
                    }
                    ii.rotation = CPoint3D(0, -90, 0);
                    for(int i = start; i < end; i++)
                    {
                        ii.position = CPoint3D(i, 0, firstTile.y + 0.05);
                        if(!scenary->getWallCollision(ii))
                            scenary->addModel(ii);
                    }
                }
            }
        case OBJECT:
            ii.rotation = CPoint3D();
            ii.position = CPoint3D((firstTile.x + secondTile.x) / 2, 0, (firstTile.y + secondTile.y) / 2);
            scenary->addModel(ii);
        }
    }
    clicked = false;
}
    
void Render2D::mouseMoveEvent(QMouseEvent *event)
{

    int x = event->x();
    int y = event->y();
    float wx, wz;

    getWorldMouseCoord(x, y, wx, wz);
    CScenary *scenary = CScenary::getInstance();
    Types t = scenary->getActiveType();

    if(wx > 0.0 && wz > 0.0)
    {
        if(clicked)
        {
            switch(t)
            {
            case WALL:
                {
                    int rtx = (int)(wx*2)/2.0 + 0.5;
                    int rty = (int)(wz*2)/2.0 + 0.5;
                    float nx, ny;
                    nx = wx - firstClick.x;
                    ny = wz - firstClick.y;
                    float length = sqrt(nx*nx+ny*ny);
                    //Abs function have problems. let's solve it momentarily.
                    if (nx < 0)
                        nx = nx * -1;
                    float sin = nx/length;
                    if(sin < SIN_45)
                    {
                        rtx = firstTile.x;
                    }
                    else
                    {
                        rty = firstTile.y;
                    }
                    secondTile.x = rtx;
                    secondTile.y = rty;
                }
            case OBJECT:
                {
                    int rtx = (int)wx;
                    int rty = (int)wz;
                    firstTile.x = rtx;
                    firstTile.y = rty;
                    CPoint3D max = CModelManager::GetInstance()->getModelSize(scenary->getActiveModel());
                    secondTile.x = rtx + max.x;
                    secondTile.y = rty + max.z;
                }
            }
        }
    }
}

void Render2D::getWorldMouseCoord(int x, int y, float &wx, float &wz)
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

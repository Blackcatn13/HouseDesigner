#include "RenderIso.h"
#include "Scenary.h"
#include "CameraManager.h"
#include "Camera.h"
#include "ModelManager.h"


RenderIso::RenderIso()
{
    camera = CameraManager::GetInstance()->GetCamera(PERSPECTIVE);
    clicked = false;
}

RenderIso::~RenderIso()
{
    if(camera)
        delete camera;
}

void RenderIso::wheelEvent(QWheelEvent *event)
{
    if(event->orientation() == Qt::Vertical)
    {
        scaleRatio += (double)(event->delta()) / 10000;
        event->Quit;
    }
}


void RenderIso::Draw()
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
            DrawLine();
            break;
        case OBJECT:
            DrawQuad();
            break;
        }
    }
}

void RenderIso::Update()
{

}

bool RenderIso::KeyEvent(int key)
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

void RenderIso::mousePressEvent(QMouseEvent *event)
{
 lastPos = event->pos();
}

void RenderIso::mouseMoveEvent(QMouseEvent *event)
{
    GLfloat dx = GLfloat(event->x() - lastPos.x()) / 120;
    GLfloat dy = GLfloat(event->y() - lastPos.y()) / 120;
    if (event->buttons() & Qt::LeftButton) {
        xRot += 180 * dy;
        yRot += 180 * dx;
    } else if (event->buttons() & Qt::RightButton) {
        xRot += 180 * dy;
        yRot += 180 * dx;
    }
    lastPos = event->pos();
}

void RenderIso::SetCameraProjection(int w, int h)
{
    camera->setProjection(w,h);
}

void RenderIso::AddCameraDistance(float d)
{
    camera->AddDistance(d);
}

void RenderIso::mouseReleaseEvent(QMouseEvent *event)
{
    if(clicked)
    {
        CScenary *scenary = CScenary::getInstance();
        Types t = scenary->getActiveType();
        clicked = false;

        switch(t)
        {
        case WALL:
            AddWall();
            break;
        case OBJECT:
            AddObject();
            break;
        }
    }    
}
    
void RenderIso::getWorldMouseCoord(int x, int y, float &wx, float &wz)
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

void RenderIso::DrawLine()
{
    glLineWidth(5);
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_LINES);
        glVertex3f(firstTile.x, 0.05, firstTile.y);
        glVertex3f(secondTile.x, 0.05, secondTile.y);
    glEnd();
    glLineWidth(1);
}

void RenderIso::DrawQuad()
{
    glColor3f(1.0, 0.2, 1.0);
    glBegin(GL_QUADS);
        glVertex3f(firstTile.x, -0.005, firstTile.y);
        glVertex3f(firstTile.x, -0.005, secondTile.y);
        glVertex3f(secondTile.x, -0.005, secondTile.y);
        glVertex3f(secondTile.x, -0.005, firstTile.y);
    glEnd();
}

void RenderIso::MoveQuad(float wx, float wz)
{
    CScenary *scenary = CScenary::getInstance();
    int rtx = (int)wx;
    int rty = (int)wz;
    firstTile.x = rtx;
    firstTile.y = rty;
    CPoint3D max = CModelManager::GetInstance()->getModelSize(scenary->getActiveModel());
    secondTile.x = rtx + max.x;
    secondTile.y = rty + max.z;
}

void RenderIso::MoveLine(float wx, float wz)
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

void RenderIso::AddObject()
{
    CScenary *scenary = CScenary::getInstance();
    Types t = scenary->getActiveType();
    ModelInfo ii;
    ii.modelName = scenary->getActiveModel();
    ii.scale = CPoint3D(1,1,1);
    ii.type = t;
    ii.rotation = CPoint3D();
    ii.position = CPoint3D((firstTile.x + secondTile.x) / 2, 0, (firstTile.y + secondTile.y) / 2);
    scenary->addModel(ii);
}

void RenderIso::AddWall()
{
    CScenary *scenary = CScenary::getInstance();
    Types t = scenary->getActiveType();
    ModelInfo ii;
    ii.modelName = scenary->getActiveModel();
    ii.scale = CPoint3D(1,1,1);
    ii.type = t;
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
            scenary->addModel(ii);
        }
    }
}

void RenderIso::FirstClickObject(float wx, float wz)
{
    CScenary *scenary = CScenary::getInstance();
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

void RenderIso::FirstClickWall(float wx, float wz)
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

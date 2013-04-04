#include "Render2D.h"
#include "Scenary.h"
#include "CameraManager.h"
#include "Camera.h"


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
        camera->move(0.6,0.0);
        gridY += 0.6;
        break;
    case Qt::Key_D:
        camera->move(0.0,0.6);
        gridX += 0.6;
        break;
    case Qt::Key_W:
        camera->move(-0.6,0.0);
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

    int x = event->x();
    int y = event->y();
    float wx, wz;

    getWorldMouseCoord(x, y, wx, wz);

    int tx = wx;
    int ty = wz;

    if(!clicked)
    {
        firstClick.x = wx;
        firstClick.y = wz;
        clicked = true;
    }
    
    qDebug() << "Tile " << tx << ", " << ty;
    qDebug() << "WX: " << wx << ", WZ: " << wz;
}

void Render2D::mouseReleaseEvent(QMouseEvent *event)
{
    if(clicked)
    {
        clicked = false;
    }
}
    
void Render2D::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "in";
    int x = event->x();
    int y = event->y();
    float wx, wz;

    getWorldMouseCoord(x, y, wx, wz);
    qDebug() << "moved to " << wx << ", " << wz;
    int tx = wx;
    int ty = wz;
    int px, py;

    if(clicked)
    {
        qDebug() << "drawing";
        px = firstClick.x - tx;
        py = firstClick.y - ty;
        vecDir.x = px;
        vecDir.y = py;
        glColor3f(1.0, 0.0, 1.0);
        glBegin(GL_LINE);
            glVertex3f(firstClick.x, 1, firstClick.y);
            glVertex3f(wx, 1, wz);
        glEnd();
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
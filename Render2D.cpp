#include "Render2D.h"
#include "Scenary.h"
#include "Camera.h"

Render2D::Render2D()
{
    camera = new Camera();
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
        camera->move(0.0,-0.2);
        break;
    case Qt::Key_S:
        camera->move(0.2,0.0);
        break;
    case Qt::Key_D:
        camera->move(0.0,0.2);
        break;
    case Qt::Key_W:
        camera->move(-0.2,0.0);
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
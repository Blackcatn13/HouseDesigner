#include "Render2D.h"
#include "Scenary.h"
#include "Camera.h"


Render2D::Render2D()
{
    camera = new Camera();
    ModelInfo ii;
    ii.modelName = "Models/ModulParet.obj";
    ii.position = CPoint3D(0,0,0);
    ii.scale = CPoint3D(1,1,1);
    ii.rotation = CPoint3D(0,90,0);
    CScenary *scene = CScenary::getInstance();
    scene->addModel(ii);
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
        break;
    case Qt::Key_S:
        camera->move(0.6,0.0);
        break;
    case Qt::Key_D:
        camera->move(0.0,0.6);
        break;
    case Qt::Key_W:
        camera->move(-0.6,0.0);
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

}

void Render2D::mouseReleaseEvent(QMouseEvent *event)
{

}
    
void Render2D::mouseMoveEvent(QMouseEvent *event)
{

}
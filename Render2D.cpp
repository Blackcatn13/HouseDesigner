#include "Render2D.h"
#include "Scenary.h"
#include "CameraManager.h"
#include "Camera.h"
#include "ModelManager.h"


Render2D::Render2D()
{
    camera = CameraManager::GetInstance()->GetCamera(ORTHOGONAL);
    clicked = false;
    actualEditMode = INSERTING;
    rotation = 0;
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
    scene->Draw();
    scene->DrawFloor();
    scene->DrawGrid();
    scene->DrawStairs();

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
        case STAIR:
            if(rotation == 0 || rotation == 3)
                DrawQuad();
            else if(rotation == 1)
                DrawInverseQuad();
            else
                DrawInverseQuad1();
            break;
        }
    }
}

void Render2D::Update()
{

}

bool Render2D::KeyEvent(int key)
{
    CScenary *scenary = CScenary::getInstance();
    Types t = scenary->getActiveType();
    bool update = true;
    Point2D move;
    switch(key)
    {
    case Qt::Key_A:
        move.y -= .6f;
        gridX -= 0.6;
        break;
    case Qt::Key_S:
        move.x -= .6f;
        gridY += 0.6;
        break;
    case Qt::Key_D:
        move.y += .6f;
        gridX += 0.6;
        break;
    case Qt::Key_W:
        move.x += .6f;
        gridY -= 0.6;
        break;
    case Qt::Key_Q:
        if(clicked)
        {
            rotation++;
            rotation = rotation % 4;
            if (t == OBJECT)
                RefreshQuad();
            else if (t == STAIR)
                RefreshQuadStair();
        }
        break;
    case Qt::Key_E:
        if(clicked)
        {
            if(rotation > 0)
                rotation--;
            else
                rotation = 3;
            rotation = rotation % 4;
            if (t == OBJECT)
                RefreshQuad();
            else if (t == STAIR)
                RefreshQuadStair();
        }
        break;
    case Qt::Key_Escape:
        if(clicked)
        {
            clicked = false;
            rotation = 0;
        }
        else
        {
            scenary->setActiveModel("");
            scenary->setActiveType(NEITHER);
            actualEditMode = SELECTING;
        }
        break;
    default:
        update = false;
    }
    camera->move(move.x, move.y, false);
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
    switch(actualEditMode)
    {
    case INSERTING:
        switch(t)
        {
        case WALL:
            FirstClickWall(wx, wz);
            break;
        case OBJECT:
            {
                CPoint3D max = CModelManager::GetInstance()->getModelSize(scenary->getActiveModel());
                if(rotation == 0 || rotation == 2)
                {
                    if(wx < scenary->getGridMaxX() - max.x +1 && wz < scenary->getGridMaxZ() - max.z +1)
                        FirstClickObject(wx, wz);
                }
                else
                {
                    if(wx < scenary->getGridMaxX() - max.z +1 && wz < scenary->getGridMaxZ() - max.x +1)
                        FirstClickObject(wx, wz);
                }
                break;
            }
        case STAIR:
            {
                if(wx < scenary->getGridMaxX() - 4 && wz < scenary->getGridMaxZ() - 1)
                    FirstClickStair(wx, wz);
                break;
            }
        }
        break;
    case SELECTING:
        float WX;
        float WY;
        float WZ;
        getWorldMouseCoord(x,y, WX, WZ);
        WX = floor((WX*2)/2 + 0.5);
        WY = floor((WY*2)/2 + 0.5);
        WZ = floor((WZ*2)/2 + 0.5);
        qDebug() << "X coord: " << WX << "Y coord: " << WZ;
        break;
    case DELETING:
        break;
    }
}

void Render2D::mouseReleaseEvent(QMouseEvent*)
{
    if(clicked)
    {
        CScenary *scenary = CScenary::getInstance();
        Types t = scenary->getActiveType();
        clicked = false;
        switch(actualEditMode)
        {
        case INSERTING:
            switch(t)
            {
            case WALL:
                AddWall();
                break;
            case OBJECT:
                AddObject();
                break;
            case STAIR:
                AddStair();
                break;
            }
            break;
        case DELETING:
            break;
        case SELECTING:
            break;
        }
        rotation = 0;
    }    
}
    
void Render2D::mouseMoveEvent(QMouseEvent *event, int, int)
{

    int x = event->x();
    int y = event->y();
    float wx, wz;

    getWorldMouseCoord(x, y, wx, wz);
    CScenary *scenary = CScenary::getInstance();
    Types t = scenary->getActiveType();

    if(wx > 0.0 && wz > 0.0 && wx < scenary->getGridMaxX() && wz < scenary->getGridMaxZ())
    {
        if(clicked)
        {
            switch(actualEditMode)
            {
            case INSERTING:
                switch(t)
                {
                case WALL:
                    MoveLine(wx, wz);
                    break;
                case OBJECT:
                    {
                        CPoint3D max = CModelManager::GetInstance()->getModelSize(scenary->getActiveModel());
                        if(rotation == 0 || rotation == 2)
                        {
                            if(wx < scenary->getGridMaxX() - max.x +1 && wz < scenary->getGridMaxZ() - max.z +1)
                                MoveQuad(wx, wz);
                        }
                        else
                        {
                            if(wx < scenary->getGridMaxX() - max.z +1 && wz < scenary->getGridMaxZ() - max.x +1)
                                MoveQuad(wx, wz);
                        }
                        break;
                    }
                case STAIR:
                    {
                        if(wx < scenary->getGridMaxX() - 4 && wz < scenary->getGridMaxZ() - 1)
                            MoveQuadStair(wx, wz);
                        break;
                    }
                }
                break;
            case DELETING:
                break;
            case SELECTING:
                break;
            }
        }
    }
}

void Render2D::getWorldMouseCoord(int x, int y, float &wx, float &wz)
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
    gluUnProject(MWX, MWY, 0, modelview, projection, viewport, &rx, &ry, &rz);
    wx = rx;
    wz = rz;
}

void Render2D::DrawLine()
{
    CScenary *scenary = CScenary::getInstance();
    glLineWidth(5);
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_LINES);
        glVertex3f(firstTile.x, 0.05 + scenary->getHeightForModels(), firstTile.y);
        glVertex3f(secondTile.x, 0.05 + scenary->getHeightForModels(), secondTile.y);
    glEnd();
    glLineWidth(1);
}

void Render2D::DrawQuad()
{
    CScenary *scenary = CScenary::getInstance();

    glColor3f(1.0f, 0.2f, 1.0f);
    glBegin(GL_QUADS);
        glVertex3f(firstTile.x, 0.005 + scenary->getHeightForModels(), firstTile.y);
        glVertex3f(firstTile.x, 0.005 + scenary->getHeightForModels(), secondTile.y);
        glVertex3f(secondTile.x, 0.005 + scenary->getHeightForModels(), secondTile.y);
        glVertex3f(secondTile.x, 0.005 + scenary->getHeightForModels(), firstTile.y);
    glEnd();
}

void Render2D::DrawInverseQuad()
{
    CScenary *scenary = CScenary::getInstance();

    glColor3f(1.0f, 0.2f, 1.0f);
    glBegin(GL_QUADS);
        glVertex3f(firstTile.x, 0.005 + scenary->getHeightForModels(), firstTile.y + 1);
        glVertex3f(secondTile.x, 0.005 + scenary->getHeightForModels(), firstTile.y + 1);
        glVertex3f(secondTile.x, 0.005 + scenary->getHeightForModels(), secondTile.y);
        glVertex3f(firstTile.x, 0.005 + scenary->getHeightForModels(), secondTile.y);
    glEnd();
}

void Render2D::DrawInverseQuad1()
{
    CScenary *scenary = CScenary::getInstance();

    glColor3f(1.0f, 0.2f, 1.0f);
    glBegin(GL_QUADS);
        glVertex3f(firstTile.x + 1, 0.005 + scenary->getHeightForModels(), firstTile.y);
        glVertex3f(secondTile.x, 0.005 + scenary->getHeightForModels(), firstTile.y);
        glVertex3f(secondTile.x, 0.005 + scenary->getHeightForModels(), secondTile.y);
        glVertex3f(firstTile.x + 1, 0.005 + scenary->getHeightForModels(), firstTile.y + 1);
    glEnd();
}

void Render2D::MoveQuad(float wx, float wz)
{
    CScenary *scenary = CScenary::getInstance();
    int rtx = (int)wx;
    int rty = (int)wz;
    firstTile.x = rtx;
    firstTile.y = rty;
    RefreshQuad();
}

void Render2D::MoveQuadStair(float wx, float wz)
{
    int rtx = (int)wx;
    int rty = (int)wz;
    firstTile.x = rtx;
    firstTile.y = rty;
    RefreshQuadStair();
}

void Render2D::MoveLine(float wx, float wz)
{
    int rtx = (int)(wx*2)/2.0 + 0.5;
    int rty = (int)(wz*2)/2.0 + 0.5;
    float nx, ny;
    nx = wx - firstClick.x;
    ny = wz - firstClick.y;
    float length = sqrt(nx*nx+ny*ny);
    //FIXME: Abs function have problems. let's solve it momentarily.
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

void Render2D::AddObject()
{
    CScenary *scenary = CScenary::getInstance();
    Types t = scenary->getActiveType();
    ModelInfo ii;
    ii.modelName = scenary->getActiveModel();
    ii.type = t;
    int namesize = ii.modelName.find_last_of('.') - ii.modelName.find_last_of('/');
    string name = ii.modelName.substr(ii.modelName.find_last_of('/') + 1, namesize - 1);
    ii.textureName.ObjectName = name;
    ii.rotation = CPoint3D(0, rotation * 90, 0);
    ii.position = CPoint3D((firstTile.x + secondTile.x) / 2, scenary->getHeightForModels(), (firstTile.y + secondTile.y) / 2);
    ii.center = CModelManager::GetInstance()->getModelCenter(ii.modelName);
    ii.radius = CModelManager::GetInstance()->getModelRadius(ii.modelName);
    ii.textureName.color.c1 = CPoint3D(0.5, 0.5, 0.5);
    ii.textureName.color.c2 = CPoint3D(1.0, 0.1, 0.1);
    ii.textureName.color.c3 = CPoint3D(0.5, 0.2, 1.0);
    ii.textureName.color.c4 = CPoint3D(0.2, 1.0, 0.1);
    ii.textureName.material.M1 = "Models/Textures/Material2.jpg";
    ii.textureName.material.M2 = "Models/Textures/Material3.jpg";
    ii.textureName.material.M3 = "Models/Textures/Material9.jpg";
    ii.textureName.material.M4 = "Models/Textures/Material8.jpg";
    scenary->addModel(ii);
}

void Render2D::AddWall()
{
    CScenary *scenary = CScenary::getInstance();
    Types t = scenary->getActiveType();
    ModelInfo ii;
    ii.modelName = scenary->getActiveModel();
    ii.type = t;
    CModelManager *cm = CModelManager::GetInstance();
    //Don't remove getmodelsize! it's needed to calculate the center and radius.
    cm->getModelSize(ii.modelName);
    ii.center = cm->getModelCenter(ii.modelName);
    ii.radius = cm->getModelRadius(ii.modelName);
    int start, end;
    if(firstTile.x == secondTile.x)
    {
        if(firstTile.y < secondTile.y)
        {
            start = firstTile.y;
            end = secondTile.y;
        }
        else
        {
            start = secondTile.y;
            end = firstTile.y;
        }
        ii.rotation = CPoint3D(0, 180, 0);
        for(int i = start; i < end; i++)
        {
            ii.position = CPoint3D(firstTile.x - 0.05 , scenary->getHeightForModels(), i);
            scenary->addModel(ii);
        }
    }
    else
    {
        if(firstTile.x < secondTile.x)
        {
            start = firstTile.x;
            end = secondTile.x;
        }
        else
        {
            start = secondTile.x;
            end = firstTile.x;
        }
        ii.rotation = CPoint3D(0, 270, 0);
        for(int i = start; i < end; i++)
        {
            ii.position = CPoint3D(i, scenary->getHeightForModels(), firstTile.y + 0.05);
            scenary->addModel(ii);
        }
    }
}

void Render2D::FirstClickObject(float wx, float wz)
{
    CScenary *scenary = CScenary::getInstance();
    if (wx > 0.0 && wz > 0.0 && wx < scenary->getGridMaxX() && wz < scenary->getGridMaxZ())
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
            if(rotation == 0 || rotation == 2)
            {
                secondTile.x = rtx + max.x;
                secondTile.y = rty + max.z;
            }
            else
            {
                secondTile.x = rtx + max.z;
                secondTile.y = rty + max.x;
            }
            clicked = true;
        }
    }
}

void Render2D::FirstClickWall(float wx, float wz)
{
    CScenary *scenary = CScenary::getInstance();
    if (wx > 0.0 && wz > 0.0 && wx < scenary->getGridMaxX() && wz < scenary->getGridMaxZ())
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

void Render2D::setEditMode(EditModes em)
{
    actualEditMode = em;
}

void Render2D::FirstClickStair(float wx, float wz)
{
    CScenary *scenary = CScenary::getInstance();
    if (wx > 0.0 && wz > 0.0 && wx < scenary->getGridMaxX() && wz < scenary->getGridMaxZ())
    {
        int rtx = (int)wx;
        int rty = (int)wz;
        if(!clicked)
        {
            firstClick.x = wx;
            firstClick.y = wz;
            firstTile.x = rtx;
            firstTile.y = rty;
            secondTile.x = rtx + 4;
            secondTile.y = rty + 1;
            clicked = true;
        }
    }
}

void Render2D::AddStair()
{
    CScenary *scenary = CScenary::getInstance();
    Types t = scenary->getActiveType();
    ModelInfo m = ModelInfo();
    m.rotation = CPoint3D(0, rotation * 90, 0);
    m.type = t;
    m.modelName = scenary->getActiveModel();
    m.center = CModelManager::GetInstance()->getModelCenter(m.modelName);
    m.radius = CModelManager::GetInstance()->getModelRadius(m.modelName);
    CPoint3D position;
    switch (rotation)
    {
    case 0:
        position = CPoint3D(firstTile.x, 0, firstTile.y);
        break;
    case 1:
        position = CPoint3D(firstTile.x, 0, firstTile.y + 1);
        break;
    case 2:
        position = CPoint3D(firstTile.x + 1, 0, firstTile.y);
        break;
    case 3:
        position = CPoint3D(firstTile.x, 0, firstTile.y);
        break;
    }
    if (!scenary->getStairCollition(position, rotation))
    {
        for(int i = 0; i < 4; ++i)
        {
            if(rotation == 0)
                m.position = CPoint3D(firstTile.x + i, 0.75 * i, firstTile.y + 0.51);
            else if (rotation == 1)
                m.position = CPoint3D(firstTile.x + 0.51, 0.75 * i, firstTile.y + 1 - i);
            else if (rotation == 2)
                m.position = CPoint3D(firstTile.x + 1- i, 0.75 * i, firstTile.y + 0.51);
            else
                m.position = CPoint3D(firstTile.x + 0.51, 0.75 * i, firstTile.y + i);
            scenary->addModel(m);
        }

        for(int i = 1; i < 4; ++i)
        {
            if(rotation == 0)
                scenary->deleteFloor(firstTile.x + i, firstTile.y + 1, scenary->getCurrentFloor() + 1);
            else if (rotation == 1)
                scenary->deleteFloor(firstTile.x, firstTile.y + 1 - i, scenary->getCurrentFloor() + 1);
            else if (rotation == 2)
                scenary->deleteFloor(firstTile.x + 1- 1 - i, firstTile.y + 1, scenary->getCurrentFloor() + 1);
            else
                scenary->deleteFloor(firstTile.x, firstTile.y + 1 + i, scenary->getCurrentFloor() + 1);
        }
    }
}

void Render2D::RefreshQuad()
{
    CScenary *scenary = CScenary::getInstance();
    CPoint3D max = CModelManager::GetInstance()->getModelSize(scenary->getActiveModel());
    if(rotation == 0 || rotation == 2)
    {
        secondTile.x = firstTile.x + max.x;
        secondTile.y = firstTile.y + max.z;
    }
    else
    {
        secondTile.x = firstTile.x + max.z;
        secondTile.y = firstTile.y + max.x;
    }
}

void Render2D::RefreshQuadStair()
{
    if (rotation == 0)
    {
        secondTile.x = firstTile.x + 4;
        secondTile.y = firstTile.y + 1;
    }
    else if(rotation == 1)
    {
        secondTile.x = firstTile.x + 1;
        secondTile.y = firstTile.y - 3;
    }
    else if(rotation == 2)
    {
        secondTile.x = firstTile.x - 3;
        secondTile.y = firstTile.y + 1;
    }
    else
    {
        secondTile.x = firstTile.x + 1;
        secondTile.y = firstTile.y + 4;
    }
}

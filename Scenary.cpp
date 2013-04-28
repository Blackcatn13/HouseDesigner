#include "Scenary.h"
#include "Util.h"
#include "ModelManager.h"

CScenary* CScenary::m_Scenary = 0;

CScenary::CScenary(void)
{
    m_WallModels = vector<vector<ModelInfo> >();
    m_ObjectModels = vector<vector<ModelInfo> >();
    addNewFloor();
    activeFloor = 0;
}


CScenary::~CScenary(void)
{
}

CScenary* CScenary::getInstance()
{
    if(m_Scenary == NULL)
        m_Scenary = new CScenary();
    return m_Scenary;
}

void CScenary::addNewFloor()
{
    m_WallModels.push_back( vector<ModelInfo>());
    m_ObjectModels.push_back( vector<ModelInfo>());
}
bool CScenary::addModel(ModelInfo m_Info)
{
    switch(m_Info.type)
    {
    case WALL:
        if(!getWall2WallCollision(m_Info) && !getWall2ObjectCollision(m_Info))
            m_WallModels[activeFloor].push_back(m_Info);
        break;
    case OBJECT:
        if(!getObject2WallCollision(m_Info) && !getObject2ObjectCollision(m_Info))
            m_ObjectModels[activeFloor].push_back(m_Info);
        break;
    }
    
    qDebug() << "Models in floor" << m_WallModels[activeFloor].size() + m_ObjectModels[activeFloor].size();
    return true;
}

bool CScenary::Draw()
{
    CModelManager *modelManager = CModelManager::GetInstance();
    if(activeFloor > m_WallModels.size())
        return false;

    for(int i = 0; i < m_WallModels[activeFloor].size(); ++i)
    {
        ModelInfo model = m_WallModels[activeFloor][i];
        glPushMatrix();
            glTranslatef(model.position.x, model.position.y, model.position.z);
            glRotatef(model.rotation.x, 1, 0 ,0);
            glRotatef(model.rotation.y, 0, 1 ,0);
            glRotatef(model.rotation.z, 0, 0 ,1);
            glScalef(model.scale.x, model.scale.y, model.scale.z);
            modelManager->Draw(model.modelName);
        glPopMatrix();
    }

    for(int i = 0; i < m_ObjectModels[activeFloor].size(); ++i)
    {
        ModelInfo model = m_ObjectModels[activeFloor][i];
        glPushMatrix();
            glTranslatef(model.position.x, model.position.y, model.position.z);
            glRotatef(model.rotation.x, 1, 0 ,0);
            glRotatef(model.rotation.y, 0, 1 ,0);
            glRotatef(model.rotation.z, 0, 0 ,1);
            glScalef(model.scale.x, model.scale.y, model.scale.z);
            modelManager->Draw(model.modelName);
        glPopMatrix();
    }
    return true;
}

bool CScenary::SaveMap(string fileName)
{
    // Implementation of the save funtion, need to write all the ModelInfo in the m_Info
    return false;
}

bool CScenary::LoadMap(string fileName)
{
    // Implementation of the read file function, need to read all the ModelInfo to the m_Info
    return false;
}

void CScenary::DrawAxis()
{
    // Eix X (vermell)
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(300.0,0.0,0.0);
    glEnd();

    // Eix Y (verd)
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,300.0,0.0);
    glEnd();

    // Eix Z (blau)
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,0.0,300.0);
    glEnd();

}

void CScenary::DrawGrid()
{
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(0, -0.01, 0);
    glVertex3f(0, -0.01, 25);
    glVertex3f(25, -0.01, 25);
    glVertex3f(25, -0.01, 0);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    for(int i = 0; i < 26; i += 1)
    {
        glVertex3f(i, 0, 0);
        glVertex3f(i, 0, 25);
        glVertex3f(0, 0, i);
        glVertex3f(25, 0, i);
    }
    glEnd();
    glEnable (GL_LINE_STIPPLE);
    glColor3f(0.1, 0.8, 0.1);
    glLineStipple(1, 0x1111);
    glBegin(GL_LINES);
    for(int i = 0; i < 25; i += 1)
    {
        glVertex3f((float)i + 0.5, 0, 0);
        glVertex3f((float)i + 0.5, 0, 25);
        glVertex3f(0, 0, (float)i + 0.5);
        glVertex3f(25, 0, (float)i + 0.5);
    }
    glEnd();
    glDisable(GL_LINE_STIPPLE);
}

void CScenary::CleanUp()
{
    CModelManager::GetInstance()->CleanUp();
    m_WallModels.clear();
    m_ObjectModels.clear();
}

bool CScenary::getWall2WallCollision(ModelInfo mi)
{
    for (int i = 0; i < m_WallModels[activeFloor].size(); ++i)
    {
        if(m_WallModels[activeFloor][i] == mi)
            return true;
    }
    return false;
}

bool CScenary::getWall2ObjectCollision(ModelInfo mi)
{
    CModelManager *modelM = CModelManager::GetInstance();
    CPoint3D size;
    CPoint3D posaux;
    ModelInfo maux;
    for (int i = 0; i < m_ObjectModels[activeFloor].size(); ++i)
    {
        maux = m_ObjectModels[activeFloor][i];
        posaux = mi.position;
        size = modelM->getModelSize(maux.modelName);
        if(mi.rotation == CPoint3D(0, 180, 0))
        {
            posaux.x += 0.05;
            if(posaux.x > (maux.position.x - size.x/2) && posaux.x < (maux.position.x + size.x/2) && posaux.z >= (maux.position.z - size.z/2) && posaux.z < (maux.position.z + size.z/2))
                return true;
        }
        if(mi.rotation == CPoint3D(0, -90, 0))
        {
            posaux.z -= 0.05;
            if(posaux.x >= (maux.position.x - size.x/2) && posaux.x < (maux.position.x + size.x/2) && posaux.z > (maux.position.z - size.z/2) && posaux.z < (maux.position.z + size.z/2))
                return true;
        }
    }
    return false;
}

bool CScenary::getObject2ObjectCollision(ModelInfo mi)
{
    return false;
}

bool CScenary::getObject2WallCollision(ModelInfo mi)
{
    return false;
}

void CScenary::setActiveModel(string model)
{
    activeModel = model;
}

void CScenary::setActiveType(Types t)
{
    activeType = t;
}
#include "Scenary.h"
#include "Util.h"
#include "ModelManager.h"

CScenary* CScenary::m_Scenary = 0;

CScenary::CScenary(void)
{
    m_Models = vector<vector<ModelInfo> >();
    addNewFloor();
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
    m_Models.push_back( vector<ModelInfo>());
}
bool CScenary::addModel(ModelInfo m_Info, int floor)
{
    m_Models[floor].push_back(m_Info);
    qDebug() << "Models in floor" << m_Models[floor].size();
    return true;
}

bool CScenary::Draw(int floor)
{
    CModelManager *modelManager = CModelManager::GetInstance();
    if(floor > m_Models.size())
        return false;

    for(int i = 0; i < m_Models[floor].size(); ++i)
    {
        ModelInfo model = m_Models[floor][i];
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
    m_Models.clear();
}

bool CScenary::getWallCollision(ModelInfo mi, int floor)
{
    bool col = false;
    for (int i = 0; i < m_Models[floor].size(); ++i)
    {
        if(m_Models[floor][i].type == WALL && !col)
        {
            col = (m_Models[floor][i] == mi);
        }
    }
    return col;
}
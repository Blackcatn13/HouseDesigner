#include "Scenary.h"
#include "Util.h"
#include "ModelManager.h"
#include "CameraManager.h"
#include "Camera.h"
#include "CameraFP.h"
#include "CameraOrtho.h"
#include "CameraPerspective.h"
#include "FrustrumManager.h"
#include "Shadermanager.h"

CScenary* CScenary::m_Scenary = 0;

CScenary::CScenary(QObject*)
{
    m_gridMaxX = 20;
    m_gridMaxZ = 20;
    m_WallModels = vector<vector<ModelInfo> >();
    m_ObjectModels = vector<vector<ModelInfo> >();
    m_FloorModels = vector<vector<ModelInfo> >();
    m_StairModels = vector<vector<ModelInfo> >();
    activeFloor = 0;
    m_nFloors = 0;
    addNewFloor();
    m_sphereDebug = false;
}

CScenary::~CScenary(void)
{
}

CScenary* CScenary::getInstance()
{
    if(m_Scenary == NULL)
        m_Scenary = new CScenary(0);
    return m_Scenary;
}

void CScenary::addNewFloor()
{
    if (m_WallModels.size() < MAXFLOORS)
    {
        m_WallModels.push_back( vector<ModelInfo>());
        m_ObjectModels.push_back( vector<ModelInfo>());
        if(m_nFloors == 0)
            m_FloorModels.push_back( vector<ModelInfo>());
        m_FloorModels.push_back( vector<ModelInfo>());
        m_StairModels.push_back( vector<ModelInfo>());
        fillFloor(); 
        m_nFloors += 1;

        //TODO: Add scenaryMat to use it with more than 1 floor.
    }
}

void CScenary::ChangeFloor(int newFloor)
{
    activeFloor = newFloor;
}

bool CScenary::addModel(ModelInfo m_Info)
{
    switch(m_Info.type)
    {
    case WALL:
        if(!getWall2WallCollision(m_Info) && !getWall2ObjectCollision(m_Info) && !getWall2StairCollision(m_Info))
        {
            m_WallModels[activeFloor].push_back(m_Info);
        }
        break;
    case OBJECT:
        if(!getObject2WallCollision(m_Info) && !getObject2ObjectCollision(m_Info) && !getObject2StairCollision(m_Info))
        {
            m_ObjectModels[activeFloor].push_back(m_Info);
        }
        break;
    case STAIR:
        m_StairModels[activeFloor].push_back(m_Info);
        break;
    }

    qDebug() << "Models in floor" << m_WallModels[activeFloor].size() + m_ObjectModels[activeFloor].size() + m_FloorModels[activeFloor].size();
    return true;
}

bool CScenary::Draw()
{
    CModelManager *modelManager = CModelManager::GetInstance();
    Camera *cam = CameraManager::GetInstance()->getCurrentCamera();
    Views camType = cam->getCameraType();
    bool drawModel = true;
    CShaderManager *shader = CShaderManager::GetInstance();

    if(activeFloor > m_WallModels.size())
        return false;
    m_PickableWall.clear();
    for(size_t i = 0; i < m_WallModels[activeFloor].size(); ++i)
    {
        ModelInfo model = m_WallModels[activeFloor][i];
        if (camType != FP)
            drawModel = true;
        else
            drawModel = CFrustrumManager::GetInstance()->sphereInFrustum(
                        model.position, 3);
        if(drawModel)
        {
            if (m_sphereDebug)
            {
                glPushMatrix();
                    glTranslatef(model.position.x, model.position.y, model.position.z);
                    glutWireSphere(3, 16, 16);
                glPopMatrix();
            }
            //Add pickable object to vector.
            m_PickableWall.push_back(std::make_pair(model, i));
            //shader->UseActiveShader(model);
            glPushMatrix();
                glColor3f(0,1,0);
                glTranslatef(model.position.x, model.position.y, model.position.z);
                glRotatef(model.rotation.x, 1, 0 ,0);
                glRotatef(model.rotation.y, 0, 1 ,0);
                glRotatef(model.rotation.z, 0, 0 ,1);
                glScalef(model.scale.x, model.scale.y, model.scale.z);
                modelManager->Draw(model.modelName);
            glPopMatrix();
            //shader->ReleaseActiveShader();
        }
    }

    m_PickableObject.clear();
    for(size_t i = 0; i < m_ObjectModels[activeFloor].size(); ++i)
    {
        ModelInfo model = m_ObjectModels[activeFloor][i];
        if (camType != FP)
            drawModel = true;
        else
            drawModel = CFrustrumManager::GetInstance()->sphereInFrustum(
                        model.position, model.radius);
        if(drawModel)
        {
            //Add pickable object to vector.
            m_PickableObject.push_back(std::make_pair(model, i));
            /*qDebug() << "Pos" << model.position.x << " " << model.position.y
                     << " " << model.position.z << "Model rad" << model.radius;*/
            if (m_sphereDebug)
            {
                glPushMatrix();
                    glTranslatef(model.position.x, model.position.y, model.position.z);
                    glutWireSphere(model.radius, 16, 16);
                glPopMatrix();
            }
            //shader->UseActiveShader(model);
            glPushMatrix();
                glColor3f(1,0,0);
                glTranslatef(model.position.x, model.position.y, model.position.z);
                glRotatef(model.rotation.x, 1, 0 ,0);
                glRotatef(model.rotation.y, 0, 1 ,0);
                glRotatef(model.rotation.z, 0, 0 ,1);
                glScalef(model.scale.x, model.scale.y, model.scale.z);
                modelManager->Draw(model.modelName);
            glPopMatrix();
            //shader->ReleaseActiveShader();
        }
    }
    return true;
}

void CScenary::DrawFloor()
{
    CModelManager *modelManager = CModelManager::GetInstance();
    Camera *cam = CameraManager::GetInstance()->getCurrentCamera();
    Views camType = cam->getCameraType();
    CShaderManager *shader = CShaderManager::GetInstance();
    bool drawModel = true;
    if(activeFloor < m_FloorModels.size())
    {
        m_PickableFloor.clear();
        for(size_t i = 0; i < m_FloorModels[activeFloor].size(); ++i)
        {
            ModelInfo model = m_FloorModels[activeFloor][i];
            if (camType != FP)
                drawModel = true;
            else
            {
                //FIXME: Control drawing of ceil and floor.
                drawModel = true;
                //drawModel = CFrustrumManager::GetInstance()->sphereInFrustum(
                            //model.position, model.radius);
            }
            if(drawModel)
            {
                //Add pickable object to vector.
                m_PickableFloor.push_back(std::make_pair(model, i));
                //shader->UseActiveShader(model);
                glPushMatrix();
                    glColor3f(1,1,0);
                    glTranslatef(model.position.x, model.position.y, model.position.z);
                    glRotatef(model.rotation.x, 1, 0 ,0);
                    glRotatef(model.rotation.y, 0, 1 ,0);
                    glRotatef(model.rotation.z, 0, 0 ,1);
                    glScalef(model.scale.x, model.scale.y, model.scale.z);
                    modelManager->Draw(model.modelName);
                glPopMatrix();
                //shader->ReleaseActiveShader();
            }
        }
    }
}

void CScenary::DrawCeil()
{
    CModelManager *modelManager = CModelManager::GetInstance();
    Camera *cam = CameraManager::GetInstance()->getCurrentCamera();
    Views camType = cam->getCameraType();
    CShaderManager *shader = CShaderManager::GetInstance();
    bool drawModel = true;
    if(activeFloor < m_FloorModels.size())
    {
        for(size_t i = 0; i < m_FloorModels[activeFloor + 1].size(); ++i)
        {
            ModelInfo model = m_FloorModels[activeFloor + 1][i];
            if (camType != FP)
                drawModel = true;
            else
            {
                //FIXME: Control drawing of ceil and floor.
                drawModel = true;
                //drawModel = CFrustrumManager::GetInstance()->sphereInFrustum(
                            //model.position - 2, model.radius);
            }
            if(drawModel)
            {
                //shader->UseActiveShader(model);
                glPushMatrix();
                    glColor3f(1,0,1);
                    glTranslatef(model.position.x, model.position.y, model.position.z);
                    glRotatef(model.rotation.x, 1, 0 ,0);
                    glRotatef(model.rotation.y, 0, 1 ,0);
                    glRotatef(model.rotation.z, 0, 0 ,1);
                    glScalef(model.scale.x, model.scale.y, model.scale.z);
                    modelManager->Draw(model.modelName);
                glPopMatrix();
                //shader->ReleaseActiveShader();
            }
        }
    }
}

void CScenary::DrawStairs()
{
    CModelManager *modelManager = CModelManager::GetInstance();
    Camera *cam = CameraManager::GetInstance()->getCurrentCamera();
    Views camType = cam->getCameraType();
    CShaderManager *shader = CShaderManager::GetInstance();
    bool drawModel = true;
    if(activeFloor < m_StairModels.size())
    {
        m_PickableStair.clear();
        for(size_t i = 0; i < m_StairModels[activeFloor].size(); ++i)
        {
            ModelInfo model = m_StairModels[activeFloor][i];
            if (camType != FP)
                drawModel = true;
            else
                drawModel = CFrustrumManager::GetInstance()->sphereInFrustum(
                            model.position, 1);
            if (m_sphereDebug)
            {
                glPushMatrix();
                    glTranslatef(model.position.x, model.position.y, model.position.z);
                    glutWireSphere(2, 16, 16);
                glPopMatrix();
            }
            if(drawModel)
            {
                //Add pickable object to vector.
                m_PickableStair.push_back(std::make_pair(model, i));
                //shader->UseActiveShader(model);
                glPushMatrix();
                    glColor3f(0, 0, 1);
                    glTranslatef(model.position.x, model.position.y, model.position.z);
                    glRotatef(model.rotation.x, 1, 0 ,0);
                    glRotatef(model.rotation.y, 0, 1 ,0);
                    glRotatef(model.rotation.z, 0, 0 ,1);
                    glScalef(model.scale.x, model.scale.y, model.scale.z);
                    modelManager->Draw(model.modelName);
                glPopMatrix();
                //shader->ReleaseActiveShader();
            }
        }
    }
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
    int heightPlane = HEIGTH * activeFloor - 1;
    int heightGrid = HEIGTH * activeFloor + 0.001;
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(0, heightPlane, 0);
    glVertex3f(0, heightPlane, m_gridMaxZ);
    glVertex3f(m_gridMaxX, heightPlane, m_gridMaxZ);
    glVertex3f(m_gridMaxX, heightPlane, 0);
    glEnd();
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_LINES);

    //Vertical lines.
    for(int i = 0; i < m_gridMaxX+1; ++i)
    {
        glVertex3f((float)i, heightGrid, 0);
        glVertex3f((float)i, heightGrid, m_gridMaxZ);
    }
    //Horizontal lines.
    for (int i = 0; i < m_gridMaxZ+1; ++i)
    {
        glVertex3f(0, heightGrid, (float)i);
        glVertex3f(m_gridMaxX, heightGrid, (float)i);
    }
    glEnd();
    glEnable (GL_LINE_STIPPLE);
    glColor3f(0.1f, 0.9f, 0.1f);
    glLineStipple(1, 0x1111);
    glBegin(GL_LINES);

    //Vertical Dashed lines.
    for(int i = 0; i < m_gridMaxX; ++i)
    {
        glVertex3f((float)i + 0.5, heightGrid, 0);
        glVertex3f((float)i + 0.5, heightGrid, m_gridMaxZ);
    }
    //Horizontal Dashed lines.
    for (int i = 0; i < m_gridMaxZ; ++i)
    {
        glVertex3f(0, heightGrid, (float)i + 0.5);
        glVertex3f(m_gridMaxX, heightGrid, (float)i + 0.5);
    }
    glEnd();
    glDisable(GL_LINE_STIPPLE);
}

void CScenary::CleanUp()
{
    CModelManager::GetInstance()->CleanUp();
    m_WallModels.clear();
    m_ObjectModels.clear();
    m_FloorModels.clear();
}

bool CScenary::getWall2WallCollision(ModelInfo mi)
{
    for (size_t i = 0; i < m_WallModels[activeFloor].size(); ++i)
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
    for (size_t i = 0; i < m_ObjectModels[activeFloor].size(); ++i)
    {
        maux = m_ObjectModels[activeFloor][i];
        posaux = mi.position;
        size = modelM->getModelSize(maux.modelName);
        if(maux.rotation == CPoint3D(0, 90, 0) || maux.rotation == CPoint3D(0, 270, 0))
        {
            CPoint3D aux = size;
            size = CPoint3D(aux.z, aux.y, aux.x); 
        }
        if(mi.rotation == CPoint3D(0, 180, 0))
        {
            posaux.x += 0.05f;
            posaux.x = ceil(posaux.x);
            if(!((posaux.x >= maux.position.x + size.x/2) ||
                (posaux.x <= maux.position.x - size.x/2) ||
                (posaux.z >= maux.position.z + size.z/2) ||
                (posaux.z < maux.position.z - size.z/2)))
                return true;
        }
        if(mi.rotation == CPoint3D(0, 270, 0))
        {
            posaux.z -= 0.05f;
            posaux.z = ceil(posaux.x);
            if(!((posaux.x >= maux.position.x + size.x/2) ||
                (posaux.x < maux.position.x - size.x/2) ||
                (posaux.z >= maux.position.z + size.z/2) ||
                (posaux.z <= maux.position.z - size.z/2)))
                return true;
        }
    }
    return false;
}

bool CScenary::getObject2ObjectCollision(ModelInfo mi)
{
    CModelManager *modelM = CModelManager::GetInstance();
    CPoint3D size1;
    CPoint3D size2;
    CPoint3D aux;
    ModelInfo maux;
    for (size_t i = 0; i < m_ObjectModels[activeFloor].size(); ++i)
    {
        maux = m_ObjectModels[activeFloor][i];
        if(maux == mi)
            return true;
        size1 = modelM->getModelSize(maux.modelName);
        if(maux.rotation == CPoint3D(0, 90, 0) || maux.rotation == CPoint3D(0, 270, 0))
        {
            aux = size1;
            size1 = CPoint3D(aux.z, aux.y, aux.x); 
        }
        size2 = modelM->getModelSize(mi.modelName);
        if(mi.rotation == CPoint3D(0, 90, 0) || mi.rotation == CPoint3D(0, 270, 0))
        {
            aux = size2;
            size2 = CPoint3D(aux.z, aux.y, aux.x); 
        }
        if(!((mi.position.x - size2.x/2 >= maux.position.x + size1.x/2) ||
            (mi.position.x + size2.x/2 <= maux.position.x - size1.x/2) ||
            (mi.position.z - size2.z/2 >= maux.position.z + size1.z/2) ||
            (mi.position.z + size2.z/2 <= maux.position.z - size1.z/2)))
            return true;
    }
    return false;
}

void CScenary::setGridMaxX(int gridMaxX)
{
    if (gridMaxX < MAXGRIDX)
    {
        m_gridMaxX = gridMaxX;
        this->DrawGrid();
    }else
        m_gridMaxX = MAXGRIDX;
}

void CScenary::setGridMaxZ(int gridMaxZ)
{
    if (gridMaxZ < MAXGRIDZ)
    {
        m_gridMaxZ = gridMaxZ;
        this->DrawGrid();
    }else
        m_gridMaxZ= MAXGRIDZ;
}

bool CScenary::getObject2WallCollision(ModelInfo mi)
{
    CModelManager *modelM = CModelManager::GetInstance();
    CPoint3D size;
    ModelInfo maux;
    CPoint3D posaux;
    for (size_t i = 0; i < m_WallModels[activeFloor].size(); ++i)
    {
        maux = m_WallModels[activeFloor][i];
        posaux = maux.position;
        size = modelM->getModelSize(mi.modelName);
        if(mi.rotation == CPoint3D(0, 90, 0) || mi.rotation == CPoint3D(0, 270, 0))
        {
            CPoint3D aux = size;
            size = CPoint3D(aux.z, aux.y, aux.x); 
        }
        if(maux.rotation == CPoint3D(0, 180, 0))
        {
            posaux.x += 0.05f;
            posaux.x = ceil(posaux.x);
            if(!((posaux.x >= mi.position.x + size.x/2) ||
                (posaux.x <= mi.position.x - size.x/2) ||
                (posaux.z >= mi.position.z + size.z/2) ||
                (posaux.z < mi.position.z - size.z/2)))
                return true;
        }
        if(maux.rotation == CPoint3D(0, 270, 0))
        {
            posaux.z -= 0.05f;
            posaux.z = ceil(posaux.z);
            if(!((posaux.x >= mi.position.x + size.x/2) ||
                (posaux.x < mi.position.x - size.x/2) ||
                (posaux.z >= mi.position.z + size.z/2) ||
                (posaux.z <= mi.position.z - size.z/2)))
                return true;
        }
    }
    return false;
}

void CScenary::setActiveModel(string model)
{
    activeModel = model;
    emit setNameModel(model);
}

void CScenary::setActiveType(Types t)
{
    activeType = t;
}

void CScenary::fillFloor()
{
    for (size_t i = 0; i < m_FloorModels.size(); ++i)
    {
        if(m_FloorModels[i].size() == 0)
        {
            for(int x = 0; x < m_gridMaxX; ++x)
            {
                for(int z = 1; z <= m_gridMaxZ; ++z)
                {
                    ModelInfo mi;
                    mi.rotation = CPoint3D();
                    mi.scale = CPoint3D(1,1,1);
                    mi.type = FLOOR;
                    mi.modelName = "Models/Sin_t_tulo.obj";
                    mi.position = CPoint3D(x, i*HEIGTH, z);
                    m_FloorModels[i].push_back(mi);
                }
            }
        }
    }
}

void CScenary::ClearFloor()
{
    m_WallModels[activeFloor].clear();
    m_ObjectModels[activeFloor].clear();
    m_StairModels[activeFloor].clear();
}

void CScenary::deleteFloor(int x, int z, int floor)
{
    if(floor < m_FloorModels.size())
    {
        vector<ModelInfo>::iterator it;
        for (it = m_FloorModels[floor].begin(); it != m_FloorModels[floor].end(); ++it)
        {
            if(it->position == CPoint3D(x, floor * HEIGTH, z))
            {
                m_FloorModels[floor].erase(it);
                break;
            }
        }
    }
}

bool CScenary::getStairCollition(CPoint3D s, int rotation)
{
    return (getStair2WallCollision(s, rotation) || getStair2ObjectCollision(s, rotation) || getStair2StairCollision(s, rotation));
}

ModelInfo CScenary::getPickedObject(float x, float y, float z, size_t &index)
{
    ModelInfo model;
    size_t indx;

    for (size_t i = 0; i < m_PickableWall.size(); ++i)
    {
        model = m_PickableWall[i].first;
        if (pow(x-model.position.x,2) + pow(y-model.position.y,2)
                + pow(y-model.position.y,2) <= pow(model.radius,2))
        {
            index = m_PickableWall[i].second;
            return model;
        }
    }

    for (size_t i = 0; i < m_PickableObject.size(); ++i)
    {
        model = m_PickableObject[i].first;
        if (pow(x-model.position.x,2) + pow(y-model.position.y,2)
                + pow(y-model.position.y,2) <= pow(model.radius,2))
        {
            index = m_PickableObject[i].second;
            return model;
        }
    }

    for (size_t i = 0; i < m_PickableObject.size(); ++i)
    {
        model = m_PickableObject[i].first;
        if (pow(x-model.position.x,2) + pow(y-model.position.y,2)
                + pow(y-model.position.y,2) <= pow(model.radius,2))
        {
            index = m_PickableObject[i].second;
            return model;
        }
    }

    for (size_t i = 0; i < m_PickableFloor.size(); ++i)
    {
        model = m_PickableFloor[i].first;
        if (pow(x-model.position.x,2) + pow(y-model.position.y,2)
                + pow(y-model.position.y,2) <= pow(model.radius,2))
        {
            index = m_PickableFloor[i].second;
            return model;
        }
    }

    for (size_t i = 0; i < m_PickableStair.size(); ++i)
    {
        model = m_PickableStair[i].first;
        if (pow(x-model.position.x,2) + pow(y-model.position.y,2)
                + pow(y-model.position.y,2) <= pow(model.radius,2))
        {
            index = m_PickableStair[i].second;
            return model;
        }
    }

    index = -1;
    return ModelInfo();
}

bool CScenary::getStair2WallCollision(CPoint3D s, int rotation)
{
    CPoint3D size;
    ModelInfo maux;
    CPoint3D posaux;
    for (size_t i = 0; i < m_WallModels[activeFloor].size(); ++i)
    {
        maux = m_WallModels[activeFloor][i];
        posaux = maux.position;
        switch (rotation)
        {
        case 0:
            size = CPoint3D(STAIR_DEEP, 0, STAIR_WIDTH);
            if(maux.rotation == CPoint3D(0, 180, 0))
            {
                posaux.x += 0.05f;
                posaux.x = ceil(posaux.x);
                if(!((posaux.x >= s.x + size.x) ||
                    (posaux.x <= s.x) ||
                    (posaux.z > s.z + size.z) ||
                    (posaux.z < s.z)))
                    return true;
            }   
            break;
        case 1:
            size = CPoint3D(STAIR_WIDTH, 0, STAIR_DEEP);
            if(maux.rotation == CPoint3D(0, 270, 0))
            {
                posaux.z -= 0.05f;
                posaux.z = ceil(posaux.z);
                if(!((posaux.x > s.x + size.x) ||
                    (posaux.x < s.x) ||
                    (posaux.z > s.z) ||
                    (posaux.z < s.z - size.z)))
                    return true;
            }
            break;
        case 2:
            size = CPoint3D(STAIR_DEEP, 0, STAIR_WIDTH);
            if(maux.rotation == CPoint3D(0, 180, 0))
            {
                posaux.x += 0.05f;
                posaux.x = ceil(posaux.x);
                if(!((posaux.x > s.x) ||
                    (posaux.x < s.x - size.x) ||
                    (posaux.z > s.z + size.z) ||
                    (posaux.z < s.z)))
                    return true;
            }
            break;
        case 3:
            size = CPoint3D(STAIR_WIDTH, 0, STAIR_DEEP);
            if(maux.rotation == CPoint3D(0, 270, 0))
            {
                posaux.z -= 0.05f;
                posaux.z = ceil(posaux.z);
                if(!((posaux.x > s.x + size.x) ||
                    (posaux.x < s.x) ||
                    (posaux.z > s.z + size.z) ||
                    (posaux.z < s.z)))
                    return true;
            }
        }
    }
    return false;
}

bool CScenary::getStair2StairCollision(CPoint3D s, int rotation)
{
    CPoint3D size;
    ModelInfo maux;
    CPoint3D posaux;
    for (size_t i = 0; i < m_StairModels[activeFloor].size(); ++i)
    {
        maux = m_StairModels[activeFloor][i];
        posaux = maux.position;
        switch (rotation)
        {
        case 0:
            size = CPoint3D(STAIR_DEEP, 0, STAIR_WIDTH);
            if(!((posaux.x >= s.x + size.x) ||
                (posaux.x + STAIR_WIDTH <= s.x) ||
                (posaux.z > s.z + size.z) ||
                (posaux.z + STAIR_WIDTH <= s.z)))
                return true;  
            break;
        case 1:
            size = CPoint3D(STAIR_WIDTH, 0, STAIR_DEEP);
            if(!((posaux.x > s.x + size.x) ||
                (posaux.x + STAIR_WIDTH < s.x) ||
                (posaux.z > s.z) ||
                (posaux.z + STAIR_WIDTH < s.z - size.z)))
                return true;
            break;
        case 2:
            size = CPoint3D(STAIR_DEEP, 0, STAIR_WIDTH);
            if(!((posaux.x > s.x) ||
                (posaux.x + STAIR_WIDTH < s.x - size.x) ||
                (posaux.z > s.z + size.z) ||
                (posaux.z + STAIR_WIDTH < s.z)))
                return true;
            break;
        case 3:
            size = CPoint3D(STAIR_WIDTH, 0, STAIR_DEEP);
            if(!((posaux.x > s.x + size.x) ||
                (posaux.x + STAIR_WIDTH < s.x) ||
                (posaux.z > s.z + size.z) ||
                (posaux.z + STAIR_WIDTH < s.z)))
                return true;
        }
    }
    return false;
}

bool CScenary::getStair2ObjectCollision(CPoint3D s, int rotation)
{ 
    CModelManager *modelM = CModelManager::GetInstance();
    CPoint3D size;
    CPoint3D size1;
    ModelInfo maux;
    CPoint3D posaux;
    for (size_t i = 0; i < m_ObjectModels[activeFloor].size(); ++i)
    {
        maux = m_ObjectModels[activeFloor][i];
        posaux = maux.position;
        size1 = modelM->getModelSize(maux.modelName);
        if(maux.rotation == CPoint3D(0, 90, 0) || maux.rotation == CPoint3D(0, 270, 0))
        {
            CPoint3D aux = size;
            size1 = CPoint3D(aux.z, aux.y, aux.x); 
        }
        switch (rotation)
        {
        case 0:
            size = CPoint3D(STAIR_DEEP, 0, STAIR_WIDTH);
            if(!((posaux.x - size1.x/2>= s.x + size.x) ||
                (posaux.x + size1.x/2 <= s.x) ||
                (posaux.z - size1.z/2>= s.z + size.z) ||
                (posaux.z + size1.z/2 <= s.z)))
                return true;  
            break;
        case 1:
            size = CPoint3D(STAIR_WIDTH, 0, STAIR_DEEP);
            if(!((posaux.x - size1.x/2 >= s.x + size.x) ||
                (posaux.x + size1.x/2 <= s.x) ||
                (posaux.z -size1.z/2 >= s.z) ||
                (posaux.z + size1.z/2 <= s.z - size.z)))
                return true;
            break;
        case 2:
            size = CPoint3D(STAIR_DEEP, 0, STAIR_WIDTH);
            if(!((posaux.x - size1.x/2 >= s.x) ||
                (posaux.x + size1.x/2 <= s.x - size.x) ||
                (posaux.z - size1.z/2>= s.z + size.z) ||
                (posaux.z + size1.z/2 <= s.z)))
                return true;
            break;
        case 3:
            size = CPoint3D(STAIR_WIDTH, 0, STAIR_DEEP);
            if(!((posaux.x - size1.x/2>= s.x + size.x) ||
                (posaux.x + size1.x/2 <= s.x) ||
                (posaux.z - size1.z/2>= s.z + size.z) ||
                (posaux.z + size1.z/2 <= s.z)))
                return true;
        }
    }
    return false;
}

bool CScenary::getObject2StairCollision(ModelInfo mi)
{
    CModelManager *modelM = CModelManager::GetInstance();
    CPoint3D size1;
    CPoint3D size2;
    CPoint3D aux;
    ModelInfo maux;
    for (size_t i = 0; i < m_StairModels[activeFloor].size(); ++i)
    {
        maux = m_StairModels[activeFloor][i];
        size1 = CPoint3D(STAIR_WIDTH, 0, STAIR_WIDTH);
        size2 = modelM->getModelSize(mi.modelName);
        if(mi.rotation == CPoint3D(0, 90, 0) || mi.rotation == CPoint3D(0, 270, 0))
        {
            aux = size2;
            size2 = CPoint3D(aux.z, aux.y, aux.x); 
        }
        if(!((mi.position.x - size2.x/2 >= maux.position.x + size1.x) ||
            (mi.position.x + size2.x/2 <= maux.position.x) ||
            (mi.position.z - size2.z/2 >= maux.position.z + size1.z) ||
            (mi.position.z + size2.z/2 <= maux.position.z)))
            return true;
    }
    return false;
}

bool CScenary::getWall2StairCollision(ModelInfo mi)
{
    CModelManager *modelM = CModelManager::GetInstance();
    CPoint3D size;
    CPoint3D posaux;
    ModelInfo maux;
    for (size_t i = 0; i < m_StairModels[activeFloor].size(); ++i)
    {
        maux = m_StairModels[activeFloor][i];
        posaux = mi.position;
        size = CPoint3D(STAIR_WIDTH, 0, STAIR_WIDTH);
        if(mi.rotation == CPoint3D(0, 180, 0))
        {
            posaux.x += 0.05f;
            posaux.x = ceil(posaux.x);
            if(!((posaux.x >= maux.position.x + size.x) ||
                (posaux.x <= maux.position.x) ||
                (posaux.z >= maux.position.z + size.z) ||
                (posaux.z < maux.position.z)))
                return true;
        }
        if(mi.rotation == CPoint3D(0, 270, 0))
        {
            posaux.z -= 0.05f;
            posaux.z = ceil(posaux.x);
            if(!((posaux.x >= maux.position.x + size.x) ||
                (posaux.x < maux.position.x) ||
                (posaux.z >= maux.position.z + size.z) ||
                (posaux.z <= maux.position.z)))
                return true;
        }
    }
    return false;
}

#include "Scenary.h"
#include "Util.h"
#include "ModelManager.h"

CScenary::CScenary(void)
{
    m_Models = vector<ModelInfo>();
}


CScenary::~CScenary(void)
{
}

bool CScenary::addModel(ModelInfo m_Info)
{
    m_Models.push_back(m_Info);
    return true;
}

bool CScenary::Draw()
{
    CModelManager *modelManager = CModelManager::GetInstance();

    for(int i = 0; i < m_Models.size(); ++i)
    {
        ModelInfo model = m_Models[i];
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

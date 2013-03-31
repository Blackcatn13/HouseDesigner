#include "ModelManager.h"
#include "Model.h"

CModelManager *CModelManager::m_ModelManager = 0;

CModelManager::CModelManager(void)
{
    m_Models = MapModel();
}


CModelManager::~CModelManager(void)
{
}

CModelManager* CModelManager::GetInstance()
{
    if(m_ModelManager == NULL)
        m_ModelManager = new CModelManager();
    return m_ModelManager;
}

bool CModelManager::Draw(string modelName)
{
    MapModel::iterator modelIterator;
    modelIterator = m_Models.find(modelName);
    if(modelIterator != m_Models.end())
        return modelIterator->second->Draw();
    else
    {
        if(LoadModel(modelName))
            return Draw(modelName);
    }
    return false;
}

bool CModelManager::LoadModel(string modelName)
{
      CModel* newModel = new CModel();
      if(newModel->LoadModel(modelName))
      {
          m_Models.insert(Model_Pair(modelName, newModel));
          return true;
      }
      return false;
}

void CModelManager::CleanUp()
{
    
    MapModel::iterator modelIt;
    for(modelIt = m_Models.begin(); modelIt != m_Models.end(); ++modelIt)
    {
        modelIt->second->CleanUp();
    }
    m_Models.clear();
    if(m_ModelManager != NULL)
        delete m_ModelManager;
    
}
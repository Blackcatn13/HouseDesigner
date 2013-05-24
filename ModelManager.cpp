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

CPoint3D CModelManager::getModelBBMax(string modelName)
{
    MapModel::iterator modelIterator;
    modelIterator = m_Models.find(modelName);
    if(modelIterator != m_Models.end())
        return modelIterator->second->getBBMax();
    else
    {
        if(LoadModel(modelName))
            return getModelBBMax(modelName);
    }
    return CPoint3D();
}

CPoint3D CModelManager::getModelBBMin(string modelName)
{
    MapModel::iterator modelIterator;
    modelIterator = m_Models.find(modelName);
    if(modelIterator != m_Models.end())
        return modelIterator->second->getBBMin();
    else
    {
        if(LoadModel(modelName))
            return getModelBBMin(modelName);
    }
    return CPoint3D();
}

CPoint3D CModelManager::getModelSize(string modelName)
{
    MapModel::iterator modelIterator;
    modelIterator = m_Models.find(modelName);
    if(modelIterator != m_Models.end())
        return modelIterator->second->getSize();
    else
    {
        if(LoadModel(modelName))
            return getModelSize(modelName);
    }
    return CPoint3D();
}

CPoint3D CModelManager::getModelCenter(string modelName)
{
    MapModel::iterator modelIterator;
    modelIterator = m_Models.find(modelName);
    if(modelIterator != m_Models.end())
        return modelIterator->second->getCenter();
    else
    {
        if(LoadModel(modelName))
            return getModelCenter(modelName);
    }
    return CPoint3D();
}

float CModelManager::getModelRadius(string modelName)
{
    MapModel::iterator modelIterator;
    modelIterator = m_Models.find(modelName);
    if(modelIterator != m_Models.end())
        return modelIterator->second->getRadius();
    else
    {
        if(LoadModel(modelName))
            return getModelRadius(modelName);
    }
    return 0.f;
}

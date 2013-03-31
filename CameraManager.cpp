#include "CameraManager.h"
#include "CameraPerspective.h"
#include "CameraOrtho.h"

CameraManager *CameraManager::m_CameraManager = 0;

CameraManager::CameraManager()
{
    m_Cameras = CameraMap();
    m_Cameras.insert(std::pair<Views, Camera*>(PERSPECTIVE, new CameraPerspective()));
    m_Cameras.insert(std::pair<Views, Camera*>(ORTHOGONAL, new CameraOrtho()));
    // TODO:
    // Afegir els inserts per els renders que falten un cop creats.

    // Resize all the render modes camera.
    SetProjection(INIT_WIDTH, INIT_HEIGHT);
    currentCamera = ORTHOGONAL;
}

CameraManager::~CameraManager()
{
}

CameraManager* CameraManager::GetInstance()
{
    if(m_CameraManager == NULL)
        m_CameraManager = new CameraManager();
    return m_CameraManager;
}

Camera* CameraManager::GetCamera(Views v)
{
    CameraMapIterator it;
    it = m_Cameras.find(v);
    return it->second;
}

void CameraManager::SetProjection(int w, int h)
{
    CameraMapIterator it = m_Cameras.begin();
    for(; it != m_Cameras.end(); ++it)
    {
        it->second->setProjection(w, h);
    }
}

void CameraManager::CleanUp()
{
    if(m_CameraManager != NULL)
        delete m_CameraManager;
    CameraMapIterator it;
    for(it = m_Cameras.begin(); it != m_Cameras.end(); ++it)
    {
        delete it->second;
    }
    m_Cameras.clear();
}

Camera* CameraManager::getCurrentCamera()
{
    return GetCamera(currentCamera);
}

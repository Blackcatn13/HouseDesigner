#include "RenderManager.h"
#include "Render.h"
#include "Render2D.h"


RenderManager *RenderManager::m_RenderManager = 0;

RenderManager::RenderManager()
{
    m_Renders = RenderMap();
    m_Renders.insert(std::pair<Modes, Render*>(EDITOR_2D, new Render2D()));
    // TODO:
    // Afegir els inserts per els renders que falten un cop creats.

    // Resize all the render modes camera.
    SetProjection(INIT_WIDTH, INIT_HEIGHT);
}

RenderManager::~RenderManager()
{
}

RenderManager* RenderManager::GetInstance()
{
    if(m_RenderManager == NULL)
        m_RenderManager = new RenderManager();
    return m_RenderManager;
}

Render* RenderManager::GetRenderMode(Modes m)
{
    RenderMapIterator it;
    it = m_Renders.find(m);
    return it->second;
}

void RenderManager::SetProjection(int w, int h)
{
    RenderMapIterator it = m_Renders.begin();
    for(; it != m_Renders.end(); ++it)
    {
        it->second->SetCameraProjection(w, h);
    }
}

void RenderManager::CleanUp()
{
    if(m_RenderManager != NULL)
        delete m_RenderManager;
    RenderMapIterator it;
    for(it = m_Renders.begin(); it != m_Renders.end(); ++it)
    {
        delete it->second;
    }
    m_Renders.clear();
}



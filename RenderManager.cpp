#include "RenderManager.h"
#include "Render.h"
#include "Render2D.h"
#include "RenderExplorer.h"


RenderManager *RenderManager::m_RenderManager = 0;

RenderManager::RenderManager(QObject*)
{
    m_Renders = RenderMap();
    m_Renders.insert(std::pair<Modes, Render*>(EDITOR_2D, new Render2D()));
    RenderExplorer* RE = new RenderExplorer();
    connect(RE, SIGNAL(changeTab()), SLOT(getChangeTab()));
    m_Renders.insert(std::pair<Modes, Render*>(EXPLORER, RE));
    // TODO:
    // Afegir els inserts per els renders que falten un cop creats.

    // Resize all the render modes camera.
    SetProjection(INIT_WIDTH, INIT_HEIGHT, EDITOR_2D);

}

RenderManager::~RenderManager()
{
}

RenderManager* RenderManager::GetInstance()
{
    if(m_RenderManager == NULL)
        m_RenderManager = new RenderManager(0);
    return m_RenderManager;
}

Render* RenderManager::GetRenderMode(Modes m)
{
    RenderMapIterator it;
    it = m_Renders.find(m);
    return it->second;
}

void RenderManager::SetProjection(int w, int h, Modes m)
{
    RenderMapIterator it = m_Renders.find(m);
    if(it != m_Renders.end())
         it->second->SetCameraProjection(w, h);
}

void RenderManager::CleanUp()
{
    RenderMapIterator it;
    for(it = m_Renders.begin(); it != m_Renders.end(); ++it)
    {
        delete it->second;
    }
    m_Renders.clear();
    if(m_RenderManager != NULL)
        delete m_RenderManager;
}

void RenderManager::getChangeTab()
{
    emit sendChangeTab();
}



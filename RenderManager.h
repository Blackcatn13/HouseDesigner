#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "Util.h"

class Render;

typedef std::map<Modes, Render*> RenderMap;
typedef std::map<Modes, Render*>::iterator RenderMapIterator;

class RenderManager
{
public:
    ~RenderManager();
    static RenderManager* GetInstance();
    Render* GetRenderMode(Modes m);
    void SetProjection(int w, int h);
    void CleanUp();
private:
    RenderManager();
    static RenderManager*   m_RenderManager;
    RenderMap               m_Renders;
};
#endif
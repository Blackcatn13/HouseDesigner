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
    static RenderManager* getInstance();
    Render* getRenderMode(Modes m);
    void setProjection(int w, int h);
private:
    RenderManager();
    static RenderManager*   m_RenderManager;
    RenderMap               m_Renders;
};
#endif
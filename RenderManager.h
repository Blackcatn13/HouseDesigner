#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "Util.h"
#include <qobject.h>

class Render;

typedef std::map<Modes, Render*> RenderMap;
typedef std::map<Modes, Render*>::iterator RenderMapIterator;

class RenderManager : public QObject
{
    Q_OBJECT
public:
    ~RenderManager();
    static RenderManager* GetInstance();
    Render* GetRenderMode(Modes m);
    void SetProjection(int w, int h, Modes mode);
    void CleanUp();
private:
    RenderManager(QObject *parent);
    static RenderManager*   m_RenderManager;
    RenderMap               m_Renders;
signals:
    void sendChangeTab();
    void releaseMouse();
public slots:
    void getChangeTab();
};
#endif
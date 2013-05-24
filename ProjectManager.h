#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include "Util.h"
class CScenary;

class CProjectManager
{
public:
    ~CProjectManager(void);
    bool SaveMap(string fileName);
    bool LoadMap(string fileName);
    static CProjectManager* getInstance();
private:
    CProjectManager(void);
    static CProjectManager* m_ProjectManager;
    int activeFloor;
    std::string getInfoFromObject(ModelInfo);
};

#endif
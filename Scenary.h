#ifndef SCENARY_H
#define SCENARY_H

#include "Util.h"
#include <vector>

class CScenary
{
public:
    ~CScenary(void);
    bool Draw(int floor);
    bool addModel(ModelInfo m_Info, int floor);
    bool SaveMap(string fileName);
    bool LoadMap(string fileName);
    static CScenary* getInstance();
    void DrawAxis();
    void DrawGrid();
    void CleanUp();
    bool getWallCollision(ModelInfo mi, int floor);
    bool getObjectCollision(ModelInfo mi, int floor);
    void addNewFloor();
private:
    CScenary(void);
    vector< vector<ModelInfo> > m_Models;  
    static CScenary* m_Scenary;
};

#endif
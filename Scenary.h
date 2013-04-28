#ifndef SCENARY_H
#define SCENARY_H

#include "Util.h"
#include <vector>

class CScenary
{
public:
    ~CScenary(void);
    bool Draw();
    bool addModel(ModelInfo m_Info);
    bool SaveMap(string fileName);
    bool LoadMap(string fileName);
    static CScenary* getInstance();
    void DrawAxis();
    void DrawGrid();
    void CleanUp();
    void setGridMaxX(int gridMaxX);
    void setGridMaxZ(int gridMaxZ);
    int getGridMaxX(){ return m_gridMaxX;}
    int getGridMaxZ(){ return m_gridMaxZ;}

private:
    CScenary(void);
    vector<ModelInfo>   m_Models;
    static CScenary*    m_Scenary;
    int                 m_gridMaxX;
    int                 m_gridMaxZ;
};

#endif

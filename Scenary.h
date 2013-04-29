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
    void addNewFloor();
    Types getActiveType() {return activeType;}
    string getActiveModel() {return activeModel;}
    void setActiveModel(string model);
    void setActiveType(Types t);

private:
    CScenary(void);
    vector< vector<ModelInfo> > m_WallModels;
    vector< vector<ModelInfo> > m_ObjectModels;
    static CScenary* m_Scenary;
    string activeModel;
    int activeFloor;
    Types activeType;
    bool getWall2WallCollision(ModelInfo mi);
    bool getWall2ObjectCollision(ModelInfo mi);
    bool getObject2WallCollision(ModelInfo mi);
    bool getObject2ObjectCollision(ModelInfo mi);
    int m_gridMaxX;
    int m_gridMaxZ;
};

#endif

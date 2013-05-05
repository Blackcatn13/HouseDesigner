#ifndef SCENARY_H
#define SCENARY_H

#include "Util.h"
#include <vector>

#define HEIGTH 3
//Maximum surface = 40*40*5 = 8000m2
#define MAXGRIDX 40
#define MAXGRIDZ 40
#define MAXFLOORS 5

class CScenary
{
public:
    ~CScenary(void);
    bool Draw();
    bool addModel(ModelInfo m_Info);
    static CScenary* getInstance();
    static int getMaxFloors() {return MAXFLOORS;}

    void DrawAxis();
    void DrawGrid();
    void DrawFloor();
    void DrawCeil();
    void CleanUp();
    void setGridMaxX(int gridMaxX);
    void setGridMaxZ(int gridMaxZ);
    int getGridMaxX(){ return m_gridMaxX;}
    int getGridMaxZ(){ return m_gridMaxZ;}
    void addNewFloor();
    void fillFloor();
    void ChangeFloor(int newFloor);
    int getCurrentFloor(){ return activeFloor; }
    int getNFloors() {return m_nFloors;}
    Types getActiveType() {return activeType;}
    string getActiveModel() {return activeModel;}
    void setActiveModel(string model);
    void setActiveType(Types t);
    vector< vector<ModelInfo> > getWalls() {return m_WallModels;}
    vector< vector<ModelInfo> > getObjects() {return m_ObjectModels;}
    vector< vector<int> > getScenaryMat();
    float getHeightForModels() {return (HEIGTH * activeFloor);}
private:
    CScenary(void);
    vector< vector<ModelInfo> > m_WallModels;
    vector< vector<ModelInfo> > m_ObjectModels;
    vector< vector<ModelInfo> > m_FloorModels;
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
    int m_nFloors;
    vector< vector<int> > m_scenaryMat;
    void setModelScenaryMat(ModelInfo m_Info, int activeFloor, int modelIndex);

};

#endif

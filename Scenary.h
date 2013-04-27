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
    bool getWallCollision(ModelInfo mi);
    bool getObjectCollision(ModelInfo mi);
    void addNewFloor();
    Types getActiveType() {return activeType;}
    string getActiveModel() {return activeModel;}
private:
    CScenary(void);
    vector< vector<ModelInfo> > m_Models;  
    static CScenary* m_Scenary;
    string activeModel;
    int activeFloor;
    Types activeType;
};

#endif
#ifndef SCENARY_H
#define SCENARY_H

#include "Util.h"
#include <vector>

class CScenary
{
public:
    CScenary(void);
    ~CScenary(void);
    bool Draw();
    bool addModel(ModelInfo m_Info);
    bool SaveMap(string fileName);
    bool LoadMap(string fileName);
    static CScenary* getInstance();
    void DrawAxis();
private:
    vector<ModelInfo> m_Models;  
    static CScenary* m_Scenary;
};

#endif
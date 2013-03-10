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

private:
    vector<ModelInfo> m_Models;    
};

#endif
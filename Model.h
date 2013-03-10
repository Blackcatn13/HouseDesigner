#ifndef MODEL_H
#define MODEL_H

#include <string>

using namespace std;

class CModel
{
public:
    CModel(void);
    ~CModel(void);
    bool Draw();
    bool LoadModel(string modelName);
};

#endif
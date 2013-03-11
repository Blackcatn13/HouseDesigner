#ifndef MODEL_H
#define MODEL_H

#include <string>

using namespace std;

class CModel
{
public:
    CModel(void);
    ~CModel(void);
    void CleanUp();
    bool Draw();
    bool LoadModel(string modelName);
private:
    const struct aiScene* scene;
};

#endif
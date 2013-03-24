#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include "Util.h"

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
    void RecursiveRender(aiNode* node);
};

#endif
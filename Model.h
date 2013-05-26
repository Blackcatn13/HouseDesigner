#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>
#include "Util.h"

#define get_min(x,y) (x<y?x:y)
#define get_max(x,y) (y>x?y:x)

class CPoint3D;

using namespace std;

class CModel
{
public:
    CModel(void);
    ~CModel(void);
    void CleanUp();
    bool Draw();
    bool LoadModel(string modelName);
    CPoint3D getBBMin() {return BBMin;}
    CPoint3D getBBMax() {return BBMax;}
    CPoint3D getSize();
    CPoint3D getCenter();
    CPoint3D getRealSize(){return realSize;}
    float getRadius();
private:
    const struct aiScene* scene;
    void RecursiveRender(aiNode* node);
    void CalculateBBAndSize(aiNode* node);
    CPoint3D BBMin;
    CPoint3D BBMax;
    CPoint3D size;
    CPoint3D center;
    CPoint3D realSize;
    float    radius;
    GLuint listName;
};

#endif

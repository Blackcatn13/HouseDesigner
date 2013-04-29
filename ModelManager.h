#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <map>
#include <string>
#include "Util.h"

using namespace std;

// Used Classes
class CModel;

// New type definitions
typedef map< string, CModel* > MapModel;
typedef pair<string, CModel*> Model_Pair;

class CModelManager
{
public:
    ~CModelManager(void);
    static CModelManager * GetInstance();
    bool Draw(string modelName);
    CPoint3D getModelBBMin(string modelName);
    CPoint3D getModelBBMax(string modelName);
    CPoint3D getModelSize(string modelName);
    void CleanUp();
private:
    static CModelManager*       m_ModelManager;
    MapModel                    m_Models;

    CModelManager(void);
    bool LoadModel(string modelName);

};

#endif
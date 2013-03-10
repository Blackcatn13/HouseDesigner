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
    CModelManager(void);
    ~CModelManager(void);
    static CModelManager * GetInstance();
    bool Draw(string modelName);
    
private:
    static CModelManager*       m_ModelManager;
    MapModel                    m_Models;

    bool LoadModel(string modelName);

};

#endif
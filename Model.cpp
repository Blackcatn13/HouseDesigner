#include "Model.h"
#include <assimp\scene.h>
#include <assimp\cimport.h>
#include <assimp\postprocess.h>

CModel::CModel(void)
{
    scene = NULL;
}


CModel::~CModel(void)
{
    aiReleaseImport(scene);
}

bool CModel::LoadModel(string modelName)
{
    scene = aiImportFile(modelName.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
    if(scene)
        return true;
    return false;
}

bool CModel::Draw()
{
    // Make the recursive call to draw the scene
    return false;
}

void CModel::CleanUp()
{
    aiReleaseImport(scene);
}

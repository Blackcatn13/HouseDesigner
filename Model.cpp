#include "Model.h"
#include <limits>
#include "Point3D.h"

CModel::CModel(void)
{
    scene = NULL;
    BBMin = CPoint3D(FLT_MAX, FLT_MAX, FLT_MAX);
    BBMax = CPoint3D(FLT_MIN, FLT_MIN, FLT_MIN);
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
    RecursiveRender(scene->mRootNode);
    return true;
}

void CModel::CleanUp()
{
    aiReleaseImport(scene);
}

void CModel::RecursiveRender(aiNode* node)
{
    glPushMatrix();
    
    for(unsigned int n = 0; n < node->mNumMeshes; ++n)
    {
        const struct aiMesh* mesh = scene->mMeshes[node->mMeshes[n]];

        // TODO:
        // Apply material code here when needed

        // TODO:
        // Ligth code here when needed

        for(unsigned int t = 0; t < mesh->mNumFaces; ++t)
        {
            const struct aiFace* face = &mesh->mFaces[t];
            GLenum face_mode;

            switch(face->mNumIndices)
            {
            case 1:
                face_mode = GL_POINTS;
                break;
            case 2:
                face_mode = GL_LINES;
                break;
            case 3:
                face_mode = GL_TRIANGLES;
                break;
            default:
                face_mode = GL_POLYGON;
                break;
            }

        glBegin(face_mode);
            for(unsigned int i = 0; i < face->mNumIndices; ++i)
            {
                int index = face->mIndices[i];
                if(mesh->mColors[0] != NULL)
                    glColor4fv((GLfloat*)&mesh->mColors[0][index]);
                if(mesh->mNormals != NULL)
                    glNormal3fv(&mesh->mNormals[index].x);
                aiVector3D tmp = mesh->mVertices[index];
                glVertex3fv(&tmp.x);
                BBMin.x = get_min(BBMin.x, tmp.x);
                BBMin.y = get_min(BBMin.x, tmp.y);
                BBMin.z = get_min(BBMin.x, tmp.z);
                BBMax.x = get_max(BBMin.x, tmp.x);
                BBMax.y = get_max(BBMin.x, tmp.y);
                BBMax.z = get_max(BBMin.x, tmp.z);
            }
        glEnd();
        }
    }

    for(unsigned n = 0; n < node->mNumChildren; ++n)
    {
        RecursiveRender(node->mChildren[n]);
    }

    glPopMatrix();
}
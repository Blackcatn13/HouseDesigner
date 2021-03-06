#include "Model.h"
#include <cfloat>
#include "Point3D.h"

CModel::CModel(void)
{
    scene = NULL;
    BBMin = CPoint3D(FLT_MAX, FLT_MAX, FLT_MAX);
    BBMax = CPoint3D(FLT_MIN, FLT_MIN, FLT_MIN);
    size = CPoint3D();
    center = CPoint3D(0,0,0);
    radius = 0;
    listName = 0;
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
    if(!glIsList(listName))
    {
        listName = glGenLists(1);
        glNewList(listName, GL_COMPILE);
        RecursiveRender(scene->mRootNode);
        glEndList();
    }
    glCallList(listName);
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
                if(mesh->HasTextureCoords(0))
				    glTexCoord2f(mesh->mTextureCoords[0][index].x, mesh->mTextureCoords[0][index].y);
                glVertex3fv(&mesh->mVertices[index].x);
                
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

void CModel::CalculateBBAndSize(aiNode* node)
{
    for(unsigned int n = 0; n < node->mNumMeshes; ++n)
    {
        const struct aiMesh* mesh = scene->mMeshes[node->mMeshes[n]];
        for(unsigned int t = 0; t < mesh->mNumFaces; ++t)
        {
            const struct aiFace* face = &mesh->mFaces[t];
            for(unsigned int i = 0; i < face->mNumIndices; ++i)
            {
                int index = face->mIndices[i];
                aiVector3D tmp = mesh->mVertices[index];
                BBMin.x = get_min(BBMin.x, tmp.x);
                BBMin.y = get_min(BBMin.y, tmp.y);
                BBMin.z = get_min(BBMin.z, tmp.z);
                BBMax.x = get_max(BBMax.x, tmp.x);
                BBMax.y = get_max(BBMax.y, tmp.y);
                BBMax.z = get_max(BBMax.z, tmp.z);

            }
        }
    }

    for(unsigned n = 0; n < node->mNumChildren; ++n)
    {
        CalculateBBAndSize(node->mChildren[n]);
        //BBMin = CPoint3D(FLT_MAX, FLT_MAX, FLT_MAX);
        //BBMax = CPoint3D(FLT_MIN, FLT_MIN, FLT_MIN);
    }
}

CPoint3D CModel::getSize()
{
    if(size == CPoint3D())
    {
        CalculateBBAndSize(scene->mRootNode);
        realSize = BBMax - BBMin;
        size.x = ceil(realSize.x);
        size.y = ceil(realSize.y);
        size.z = ceil(realSize.z);
    }
    return size;
}

CPoint3D CModel::getCenter()
{
    center = (BBMax + BBMin) / 2.f;
    return center;
}

float CModel::getRadius()
{
    //Calculate radius of the model;
    float distX = BBMax.x - center.x;
    float distY = BBMax.y - center.y;
    float distZ = BBMax.z - center.z;
    radius = max(max(distX, distY), distZ);
    return radius;
}

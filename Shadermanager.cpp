#include "Shadermanager.h"
#include "TextureManager.h"

CShaderManager *CShaderManager::m_ShaderManager = 0;

CShaderManager::CShaderManager(void)
{
    m_ShadersName = MapNames();
    m_ShadersName[LIGHTSHADER] = "Shaders/phong";
    m_ShadersName[TEXTURE] = "Shaders/mask";
    m_ShadersName[SIMPLE] = "Shaders/texture";
    //selShader init.
    m_SelShader = NOSHADER;
    // Create Shaders and compile it for best performance.
    for (MapNames::iterator it = m_ShadersName.begin(); it != m_ShadersName.end(); ++it)
    {
        QGLShader *Fshader = new QGLShader(QGLShader::Fragment);
        Fshader->compileSourceFile(QString(it->second.c_str()) + ".frag");
        QGLShader *Vshader = new QGLShader(QGLShader::Vertex);
        Vshader->compileSourceFile(QString(it->second.c_str()) + ".vert");
        m_FragmentShaders[it->first] = Fshader;
        m_VertexShaders[it->first] = Vshader;
    }
    m_ShaderP = new QGLShaderProgram();
}

CShaderManager::~CShaderManager(void)
{
}

CShaderManager* CShaderManager::GetInstance()
{
    if(m_ShaderManager == 0)
        m_ShaderManager = new CShaderManager;
    return m_ShaderManager;
}

void CShaderManager::CleanUp()
{
    if(m_ShaderManager != NULL)
        delete m_ShaderManager;
    if(m_ShaderP != NULL)
        m_ShaderP->removeAllShaders();
        delete m_ShaderP;
    for(MapNames::iterator it = m_ShadersName.begin(); it != m_ShadersName.end(); ++it)
    {
        delete m_VertexShaders[it->first];
        delete m_FragmentShaders[it->first];
    }
    m_VertexShaders.clear();
    m_FragmentShaders.clear();
    m_ShadersName.clear();
}

bool CShaderManager::setShader(sType type)
{
    MapNames::iterator ShaderIter;
    ShaderIter = m_ShadersName.find(type);
    if (ShaderIter != m_ShadersName.end())
    {
        m_SelShader = type;
        if(m_SelShader != NOSHADER)
        {
            m_ShaderP->addShader(m_FragmentShaders[m_SelShader]);
            m_ShaderP->addShader(m_VertexShaders[m_SelShader]);
        }
        return true;
    }
    return false;
}

void CShaderManager::UseActiveShader(ModelInfo mi)
{
    switch(m_SelShader)
    {
    case TEXTURE:
        glActiveTexture(GL_TEXTURE1);
        m_ShaderP->setUniformValue(m_ShaderP->uniformLocation("material1"), 0);
        CTextureManager::GetInstance()->Bind(mi.textureName.material.M1);
        glActiveTexture(GL_TEXTURE2);
        m_ShaderP->setUniformValue(m_ShaderP->uniformLocation("material2"), 0);
        CTextureManager::GetInstance()->Bind(mi.textureName.material.M2);
        glActiveTexture(GL_TEXTURE3);
        m_ShaderP->setUniformValue(m_ShaderP->uniformLocation("material3"), 0);
        CTextureManager::GetInstance()->Bind(mi.textureName.material.M3);
        glActiveTexture(GL_TEXTURE4);
        m_ShaderP->setUniformValue(m_ShaderP->uniformLocation("mask"), 0);
        CTextureManager::GetInstance()->Bind(mi.textureName.material.Mask);
    case SIMPLE:
    case LIGHTSHADER:
        glActiveTexture(GL_TEXTURE0);
        m_ShaderP->setUniformValue(m_ShaderP->uniformLocation("base"), 0);
        CTextureManager::GetInstance()->Bind(mi.textureName.base);
        break;
    }
    m_ShaderP->bind();
}

void CShaderManager::ReleaseActiveShader()
{
    m_ShaderP->release();
}
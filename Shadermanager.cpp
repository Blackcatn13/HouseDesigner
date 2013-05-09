#include "Shadermanager.h"

CShaderManager *CShaderManager::m_ShaderManager = 0;

CShaderManager::CShaderManager(void)
{
    m_Shaders = MapShader();
    m_Shaders["Shader1"] = LIGHT;
    m_Shaders["Shader2"] = TEXTURE;
    m_Shaders["Shader3"] = NEITHER;
    //selShader init.
    m_SelShader.first = "";
    m_SelShader.second = NEITHER;
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
}

bool CShaderManager::setShader(string shaderName, sType type)
{
    MapShader::iterator ShaderIter;
    ShaderIter = m_Shaders.find(shaderName);
    if (ShaderIter->first == shaderName && ShaderIter->second == type)
    {
        m_SelShader.first = shaderName;
        m_SelShader.second = type;
        return true;
    }
    return false;
}

#include "Shadermanager.h"

CShaderManager *CShaderManager::m_ShaderManager = 0;

CShaderManager::CShaderManager(void)
{
    string arr[] = { "Shader1", "Shader2", "Shader3" };
    m_Shaders = vector<string>(arr, arr + sizeof(arr)/sizeof(arr[0]));
    m_SelShader = "";
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

bool CShaderManager::setShader(string shaderName)
{
    //FIXME: Need check if shaderName exists.
    bool test = true;
    if (test)
        m_SelShader = shaderName;
    return test;
}

#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <map>
#include <string>
#include <vector>
using namespace std;

enum sType {LIGHT, TEXTURE, NEITHER};
typedef map< string, sType > MapShader;
typedef pair< string, sType> pair_Shader;

class CShaderManager
{
public:
    ~CShaderManager(void);
    static CShaderManager* GetInstance();
    void CleanUp();
    bool setShader(string shaderName, sType type);
    pair_Shader getShader (){return m_SelShader;}
private:
    static CShaderManager*  m_ShaderManager;
    CShaderManager(void);
    pair_Shader             m_SelShader;
    MapShader               m_Shaders;
};

#endif // SHADERMANAGER_H

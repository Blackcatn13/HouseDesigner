#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <string>
#include <vector>
using namespace std;

class CShaderManager
{
public:
    ~CShaderManager(void);
    static CShaderManager* GetInstance();
    void CleanUp();
    bool setShader(string shaderName);
    string getShader (){return m_SelShader;}
private:
    static CShaderManager* m_ShaderManager;
    CShaderManager(void);
    string m_SelShader;
    vector<string> m_Shaders;
};

#endif // SHADERMANAGER_H

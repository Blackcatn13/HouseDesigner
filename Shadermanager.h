#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "Util.h"
#include <map>
#include <string>
#include <vector>
#include <QGLShader>
#include <qglshaderprogram.h>

using namespace std;

typedef map< sType, string > MapNames;
typedef pair< sType, string> pair_Shader;
typedef map< sType, QGLShader*> ShaderMap;

class CShaderManager
{
public:
    ~CShaderManager(void);
    static CShaderManager* GetInstance();
    void CleanUp();
    bool setShader(sType type);
    sType getShader (){return m_SelShader;}
    void UseActiveShader(ModelInfo mi);
    void ReleaseActiveShader();
    void setShaderProgram(QGLShaderProgram *sp) {m_ShaderP = sp;}
    void CompileShaders(const QGLContext *c);

private:
    static CShaderManager*  m_ShaderManager;
    CShaderManager(void);
    QGLShaderProgram*       m_ShaderP;
    sType                   m_SelShader;
    MapNames                m_ShadersName;
    ShaderMap               m_FragmentShaders;
    ShaderMap               m_VertexShaders;
};

#endif // SHADERMANAGER_H

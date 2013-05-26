#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "Util.h"
#include <map>
#include <string>
#include <vector>
#include <QGLShader>
#include <qglshaderprogram.h>

#define PATHTEXTURES "BaseTextures/"
#define PNG ".png"
#define MASK "Mask.png"
#define OVER "Over.png"

using namespace std;

typedef map< sType, string > MapNames;
typedef map< sType, QGLShaderProgram*> ProgramMap;

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
    void initShaders(const QGLContext* sc, sType type);

private:
    static CShaderManager*  m_ShaderManager;
    CShaderManager(void);
    const QGLContext*       m_ShaderC;
    sType                   m_SelShader;
    MapNames                m_ShadersName;
    ProgramMap              m_ProgramShaders;
};

#endif // SHADERMANAGER_H

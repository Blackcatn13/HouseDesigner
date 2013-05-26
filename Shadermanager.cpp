#include "Shadermanager.h"
#include "TextureManager.h"

CShaderManager *CShaderManager::m_ShaderManager = 0;

CShaderManager::CShaderManager(void)
{
    m_ShadersName = MapNames();
    //m_ShadersName[LIGHTSHADER] = "Shaders/phong";
    m_ShadersName[TEXTURE] = "Shaders/mask";
    m_ShadersName[SIMPLE] = "Shaders/texture";
    m_ShadersName[ONETEXTURE] = "Shaders/onetexture";
    //selShader init.
    m_SelShader = NOSHADER;
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
    for(ProgramMap::iterator it = m_ProgramShaders.begin(); it != m_ProgramShaders.end(); ++it)
    {
        it->second->removeAllShaders();
        delete m_ProgramShaders[it->first];
    }

    m_ProgramShaders.clear();
    m_ShadersName.clear();

    if(m_ShaderManager != NULL)
        delete m_ShaderManager;
}

bool CShaderManager::setShader(sType type)
{
    m_SelShader = type;
    return true;
}

void CShaderManager::UseActiveShader(ModelInfo mi)
{
    //m_ShaderP->link();
    if(mi.type == WALL || mi.type == FLOOR)
    {
        if(m_SelShader != ONETEXTURE)
        {
            setShader(ONETEXTURE);
            qDebug() << "Changing to ONETEXTURE";
        }
    }
    if(mi.type == OBJECT)
    {
        if(m_SelShader != TEXTURE)
        {
            setShader(TEXTURE);
            qDebug() << "Changing to TEXTURE";
        }
    }

    QGLShaderProgram *m_ShaderP = m_ProgramShaders[m_SelShader];
    bool r;
    r = m_ShaderP->bind();
    if(!r)
        qDebug() << "Error" << m_ShaderP->log();
    glEnable(GL_TEXTURE_2D);
    switch(m_SelShader)
    {
    case SIMPLE:
    case LIGHTSHADER:
        glActiveTexture(GL_TEXTURE0);
        CTextureManager::GetInstance()->Bind(PATHTEXTURES + mi.textureName.ObjectName + PNG);
        m_ShaderP->setUniformValue(m_ShaderP->uniformLocation("base"), 0);
        
        glActiveTexture(GL_TEXTURE1);
        CTextureManager::GetInstance()->Bind(PATHTEXTURES + mi.textureName.ObjectName + OVER);
        m_ShaderP->setUniformValue(m_ShaderP->uniformLocation("over"), 1);
        break;
    case ONETEXTURE:
        glActiveTexture(GL_TEXTURE0);
        CTextureManager::GetInstance()->Bind(mi.textureName.material.M1);
        m_ShaderP->setUniformValue(m_ShaderP->uniformLocation("base"), 0);

        m_ShaderP->setUniformValue(m_ShaderP->uniformLocation("m1color"), mi.textureName.color.c1.x, mi.textureName.color.c1.y, mi.textureName.color.c1.z, 0);
        break;
    case TEXTURE:
        glActiveTexture(GL_TEXTURE0);
        CTextureManager::GetInstance()->Bind(PATHTEXTURES + mi.textureName.ObjectName + PNG);
        m_ShaderP->setUniformValue(m_ShaderP->uniformLocation("base"), 0);
        
        glActiveTexture(GL_TEXTURE1);
        CTextureManager::GetInstance()->Bind(PATHTEXTURES + mi.textureName.ObjectName + OVER);
        m_ShaderP->setUniformValue(m_ShaderP->uniformLocation("over"), 1);

        glActiveTexture(GL_TEXTURE2);
        CTextureManager::GetInstance()->Bind(mi.textureName.material.M1);
        m_ShaderP->setUniformValue(m_ShaderP->uniformLocation("m1"), 2);

        glActiveTexture(GL_TEXTURE3);
        CTextureManager::GetInstance()->Bind(mi.textureName.material.M2);
        m_ShaderP->setUniformValue(m_ShaderP->uniformLocation("m2"), 3);
        
        glActiveTexture(GL_TEXTURE4);
        CTextureManager::GetInstance()->Bind(mi.textureName.material.M3);
        m_ShaderP->setUniformValue(m_ShaderP->uniformLocation("m3"), 4);
        
        glActiveTexture(GL_TEXTURE5);
        CTextureManager::GetInstance()->Bind(mi.textureName.material.M4);
        m_ShaderP->setUniformValue(m_ShaderP->uniformLocation("m4"), 5);
        
        glActiveTexture(GL_TEXTURE6);
        bool alpha = CTextureManager::GetInstance()->Bind(PATHTEXTURES + mi.textureName.ObjectName + MASK);
        m_ShaderP->setUniformValue(m_ShaderP->uniformLocation("mask"), 6);
        m_ShaderP->setUniformValue(m_ShaderP->uniformLocation("alpha"), alpha);

        m_ShaderP->setUniformValue(m_ShaderP->uniformLocation("c1"), mi.textureName.color.c1.x, mi.textureName.color.c1.y, mi.textureName.color.c1.z, 0);
        m_ShaderP->setUniformValue(m_ShaderP->uniformLocation("c2"), mi.textureName.color.c2.x, mi.textureName.color.c2.y, mi.textureName.color.c2.z, 0);
        m_ShaderP->setUniformValue(m_ShaderP->uniformLocation("c3"), mi.textureName.color.c3.x, mi.textureName.color.c3.y, mi.textureName.color.c3.z, 0);
        m_ShaderP->setUniformValue(m_ShaderP->uniformLocation("c4"), mi.textureName.color.c4.x, mi.textureName.color.c4.y, mi.textureName.color.c4.z, 0);
        break;
    }
}

void CShaderManager::ReleaseActiveShader()
{
    glDisable(GL_TEXTURE_2D);
    m_ProgramShaders[m_SelShader]->release();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE6);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void CShaderManager::initShaders(const QGLContext* sc, sType type)
{
    m_ShaderC = sc;
    m_SelShader = type;
    m_ProgramShaders[SIMPLE] = new QGLShaderProgram(m_ShaderC);
    m_ProgramShaders[TEXTURE] = new QGLShaderProgram(m_ShaderC);
    m_ProgramShaders[ONETEXTURE] = new QGLShaderProgram(m_ShaderC);

    bool r;
    // Create Shaders and compile it for best performance.
    for (MapNames::iterator it = m_ShadersName.begin(); it != m_ShadersName.end(); ++it)
    {
        QGLShader *Fshader = new QGLShader(QGLShader::Fragment, m_ShaderC);
        r = Fshader->compileSourceFile(QString(it->second.c_str()) + ".frag");
        if(!r)
            qDebug() << "Fragment: " << Fshader->log();
        QGLShader *Vshader = new QGLShader(QGLShader::Vertex, m_ShaderC);
        r = Vshader->compileSourceFile(QString(it->second.c_str()) + ".vert");
        if(!r)
            qDebug() << "Vertex: " << Vshader->log();
        // Add the shaders to the program
        m_ProgramShaders[it->first]->addShader(Vshader);
        m_ProgramShaders[it->first]->addShader(Fshader);
        m_ProgramShaders[it->first]->link();
    }
}

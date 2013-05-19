#include "Texture.h"
#include <QtOpenGL/QGLWidget>
#include "TextureManager.h"

CTexture::CTexture(void)
{
    m_Name = 0;
}

CTexture::~CTexture(void)
{

}

bool CTexture::LoadTexture(string textureName)
{
    if(!texture.load(textureName.c_str()))
        return false;
    texture = QGLWidget::convertToGLFormat(texture);
    if(texture.isNull())
        return false;
    return true;     
}

bool CTexture::Bind()
{
    if(m_Name == 0)
        m_Name = CTextureManager::getName();
    glBindTexture(GL_TEXTURE_2D, m_Name);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA,
            texture.width(), texture.height(),
            0, GL_RGBA, GL_UNSIGNED_BYTE, texture.bits() );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    return true;
}

void CTexture::CleanUp()
{  
}

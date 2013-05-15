#include "TextureManager.h"
#include "Texture.h"
CTextureManager *CTextureManager::m_TextureManager = 0;

CTextureManager::CTextureManager(void)
{
    m_Textures = MapTexture();
}


CTextureManager::~CTextureManager(void)
{
}

CTextureManager* CTextureManager::GetInstance()
{
    if(m_TextureManager == NULL)
        m_TextureManager = new CTextureManager();
    return m_TextureManager;
}

bool CTextureManager::Draw(string TextureName)
{
    MapTexture::iterator TextureIterator;
    TextureIterator = m_Textures.find(TextureName);
    if(TextureIterator != m_Textures.end())
        return TextureIterator->second->Draw();
    else
    {
        if(LoadTexture(TextureName))
            return Draw(TextureName);
    }
    return false;
}

bool CTextureManager::LoadTexture(string TextureName)
{
      CTexture* newTexture = new CTexture();
      if(newTexture->LoadTexture(TextureName))
      {
          m_Textures.insert(Texture_Pair(TextureName, newTexture));
          return true;
      }
      return false;
}

void CTextureManager::CleanUp()
{
    MapTexture::iterator TextureIt;
    for(TextureIt = m_Textures.begin(); TextureIt != m_Textures.end(); ++TextureIt)
        TextureIt->second->CleanUp();
    m_Textures.clear();
    if(m_TextureManager != NULL)
        delete m_TextureManager;

}

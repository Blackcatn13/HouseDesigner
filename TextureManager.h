#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <map>
#include <string>
#include "Util.h"

using namespace std;

// Used Classes
class CTexture;

// New type definitions
typedef map< string, CTexture* > MapTexture;
typedef pair< string, CTexture* > Texture_Pair;

class CTextureManager
{
public:
    ~CTextureManager(void);
    static CTextureManager * GetInstance();
    bool Bind(string TextureName);
    void CleanUp();
    static GLuint getName();
private:
    static CTextureManager*    m_TextureManager;
    MapTexture                 m_Textures;
    static GLuint              m_NextTextureName;
    CTextureManager(void);
    bool LoadTexture(string textureName);
};

#endif // TEXTUREMANAGER_H

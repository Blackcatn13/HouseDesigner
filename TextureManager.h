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
    bool Draw(string textureName);
    void CleanUp();
private:
    static CTextureManager*     m_TextureManager;
    MapTexture                 m_Textures;

    CTextureManager(void);
    bool LoadTexture(string textureName);
};

#endif // TEXTUREMANAGER_H

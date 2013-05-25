#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "Util.h"
#include <qimage.h>

using namespace std;

class CTexture
{
public:
    CTexture(void);
    ~CTexture(void);
    void CleanUp();
    bool LoadTexture(string textureName);
    bool Bind();
private:
    QImage texture;
    GLuint m_Name;
    bool hasAlpha;
};

#endif // TEXTURE_H

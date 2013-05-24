#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "Util.h"

using namespace std;

class CTexture
{
public:
    CTexture(void);
    ~CTexture(void);
    void CleanUp();
    bool Draw();
    bool LoadTexture(string textureName);
private:
};

#endif // TEXTURE_H

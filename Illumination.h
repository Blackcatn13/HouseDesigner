#ifndef ILLUMINATION_H
#define ILLUMINATION_H

#include "Util.h"

class Illumination
{
public:
    Illumination();
    ~Illumination();
    void update(void);
    void draw(void);
    void move(float ah, float av);

private:
    float pos[4],dif[4],amb[4],spe[4];
};

#endif // ILLUMINATION_H

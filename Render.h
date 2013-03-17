#ifndef RENDER_H
#define RENDER_H

#include "Util.h"

class Render
{
public:
    void virtual Draw() = 0;
    void virtual Update() = 0;
    bool virtual KeyEvent(int key) = 0;
    void virtual SetCameraProjection(int w, int h) = 0;
    void virtual AddCameraDistance(float d) = 0;
    Render();
    ~Render();
};

#endif
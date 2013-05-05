#ifndef CAMERA_H
#define CAMERA_H

#include "Util.h"

class Camera
{
public:
    Camera();
    ~Camera();

    void virtual setProjection(int w,int h) = 0;
    void virtual update() = 0;
    void virtual move(float ah, float av, bool fly) = 0;
    void virtual AddDistance(float d) = 0;
    float virtual getZoom() = 0;
    void virtual AddYawAndPitch(float yaw, float pitch) = 0;
};

#endif // CAMERA_H
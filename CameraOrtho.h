#ifndef CAMERA_ORTHO_H
#define CAMERA_ORTHO_H

#include "Util.h"
#include "Camera.h"

class CameraOrtho : public Camera
{
public:
    CameraOrtho();
    ~CameraOrtho();

    void setProjection(int w,int h);
    void update();
    void move(float ah, float av, bool fly);
    void AddDistance(float d);
    float getZoom() {return orthoZoom;}
    void AddYawAndPitch(float yaw, float pitch) {;}
private:
    float orthoZoom, orthoAngleH, orthoAngleV;
};

#endif // CAMERA_ORTHO_H

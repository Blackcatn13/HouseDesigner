#ifndef CAMERA_H
#define CAMERA_H

#include "Util.h"

class Camera
{
public:
    Camera();
    ~Camera();

    void setProjection(int w,int h);
    Views getView();
    void update();
    void move(float ah, float av);
    void AddDistance(float d);
private:
    float R,angleh,anglev;
    float Cnear,Cfar;
};

#endif // CAMERA_H

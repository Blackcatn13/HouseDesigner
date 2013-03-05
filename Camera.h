#ifndef CAMERA_H
#define CAMERA_H

#include "Util.h"

class Camera
{
public:
    Camera();
    ~Camera();

    void setProjection(int w,int h, int i=0);
    Views getView();
    void update(int camera_index=0);
    void move(float ah, float av);
    void setView(Views view);

private:
    float R,angleh,anglev;
    float Cnear,Cfar;
    Views currentView;
};

#endif // CAMERA_H

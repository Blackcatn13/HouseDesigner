#ifndef CAMERA_PERSPECTIVE_H
#define CAMERA_PERSPECTIVE_H

#include "Util.h"
#include "Camera.h"
#include <QMouseEvent>

class CameraPerspective : public Camera
{
public:
    CameraPerspective();
    ~CameraPerspective();

    void setProjection(int w,int h);
    void update();
    void move(float ah, float av);
    void AddDistance(float d);
    float getZoom() {return R;}
private:
    float R,angleh,anglev;
    float Cnear,Cfar;
};

#endif // CAMERA_PERSPECTIVE_H

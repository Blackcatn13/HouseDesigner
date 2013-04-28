#ifndef CAMERA_FP_H
#define CAMERA_FP_H

#include "Util.h"
#include "Camera.h"

#define toRad(v) (v*PI/180)

class CameraFP : public Camera
{
public:
    CameraFP();
    ~CameraFP();

    void setProjection(int w,int h);
    void update();
    void move(float f, float s);
    void AddDistance(float d) {;}
    float getZoom() {return 1;}
    void AddYawAndPitch(float yaw, float pitch);
private:
    float m_yaw, m_pitch, speedy, speedp, speedf;
    float Cnear,Cfar;
    CPoint3D position;

};

#endif // CAMERA_ORTHO_H
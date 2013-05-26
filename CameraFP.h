#ifndef CAMERA_FP_H
#define CAMERA_FP_H

#include "Util.h"
#include "Camera.h"
#include "Plane.h"
#include "FrustrumManager.h"

#define toRad(v) (v*PI/180.0)
#define NPLANES 6


class CameraFP : public Camera
{
public:
    CameraFP();
    ~CameraFP();

    void setProjection(int w,int h);
    void update();
    void move(float f, float s, bool fly);
    void AddDistance(float);
    float getZoom() {return 1;}
    void AddYawAndPitch(float yaw, float pitch);
    Views getCameraType(){return FP;}
private:
    float m_yaw, m_pitch, speedy, speedp, speedf, mRatio;
    float mAngle;
    CPoint3D position, dir, up;
    float Cnear,Cfar;
    bool flying;
};

#endif // CAMERA_FP_H

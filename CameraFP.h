#ifndef CAMERA_FP_H
#define CAMERA_FP_H

#include "Util.h"
#include "Camera.h"
#include "Plane.h"

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
    void AddDistance(float) {;}
    float getZoom() {return 1;}
    void AddYawAndPitch(float yaw, float pitch);
    bool testSphereFrustrum(CPoint3D center, float radius);
private:
    //Define frustum planes.
    enum{TOP=0, BOTTOM=1, LEFT=2, RIGHT=3, NEAR=4, FAR=5};
    float m_yaw, m_pitch, speedy, speedp, speedf;
    float Cnear,Cfar;
    CPoint3D position, dir, up;
    //Create frustum planes
    CPlane plane[NPLANES];
    //Points of planes
    //N: Near, F: Far, T: Top, B: Bottom, R: Right, L: Left
    CPoint3D ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr;
    //Define sizes of near and far planes.
    float mNearWidth, mNearHeight, mFarWidth, mFarHeight;
    float mNearD, mFarD, mAngle, mRatio, mtan;
    void SetCamValues();
    void setCamSpecs();
    void CalculateFrustrumPlanes();
};

#endif // CAMERA_FP_H

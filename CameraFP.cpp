#include "CameraFP.h"
#include <cmath>

CameraFP::CameraFP()
{
    glMatrixMode(GL_POSITION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    Cnear = .1f;
    Cfar = 1000;
    m_yaw = 0;
    m_pitch = 0;
    speedy = speedp = speedf = 1.0;
    position = CPoint3D(-5, 1.5, 0);
    dir = CPoint3D(0, 0, 0);
    up = CPoint3D(0,1,0);
}

void CameraFP::setProjection(int w, int h)
{

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    mRatio = w/h;
    mAngle = 60.0f;
    if(w >= h)
        gluPerspective(mAngle, mRatio, Cnear, Cfar);
    else
        gluPerspective(mAngle , mRatio, Cnear, Cfar);
    SetCamValues();
}

void CameraFP::update()
{

    float yaw = toRad(m_yaw);
    float pitch = toRad(m_pitch);
    dir.x = cos(yaw) * cos(pitch);
    dir.y = sin(pitch);
    dir.z = sin(yaw) * cos(pitch);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(position.x, position.y, position.z,
        position.x + dir.x, position.y + dir.y, position.z + dir.z,
        up.x, up.y, up.z);
    setCamSpecs();
}

void CameraFP::move(float f, float s, bool fly)
{
    CPoint3D addPos = CPoint3D();
    float yaw = toRad(m_yaw);
    float p = toRad(m_pitch);
    addPos.x = f * cos(yaw) * cos(p) + s * cos(yaw - PI_2);
    addPos.z = f * sin(yaw) * cos(p) + s * sin(yaw - PI_2);
    if (fly)
        addPos.y = sin(p);
    
    position += addPos;
    qDebug() << "Position to add: " << addPos.x << " , " << addPos.y << " , " << addPos.z;
    qDebug() << "Actual Position: " << position.x << " , " << position.y << " , " << position.z;
}

void CameraFP::AddYawAndPitch(float yaw, float pitch)
{
    m_yaw += yaw;
    m_pitch += pitch;

    if(m_pitch < -90)
        m_pitch = -90;
    if(m_pitch > 90)
        m_pitch = 90;
    if(m_yaw < -180)
        m_yaw += 360;
    if(m_yaw > 180)
        m_yaw -= 360;
}

//This function gets same inputs as gluPerspective...
//gluPerspective(mAngle, mRatio, Cnear, Cfar);
void CameraFP::SetCamValues()
{
    mtan = (float)tan(toRad(mAngle)*0.5);

    mNearHeight = mNearD * mtan;
    mFarHeight = mFarD * mtan;

    mNearWidth = mNearD * mRatio;
    mFarWidth = mFarD * mRatio;
}

//gluLookAt: Eye(position of camera), center(point to look), Up
void CameraFP::setCamSpecs()
{
    //X, Y and Z.
    CPoint3D X, Y, Z;
    //Vector of direction is dir.
    //Z axis of a camera is the opposite direction from the looking direction.
    Z = dir * -1;
    Z.Normalize();

    //X axis of camera
    X = up * Z;
    X.Normalize();

    //X axis of camera (real "up" vector).
    Y = Z * X;

    //Calculate the centers of the near (nc) and far (fc) planes.
    CPoint3D nc = position - Z * mNearD;
    CPoint3D fc = position - Z * mFarD;

    //Corners of the near plane.
    ntr = nc + Y * mNearHeight + X * mNearWidth;
    ntl = nc + Y * mNearHeight - X * mNearWidth;
    nbr = nc - Y * mNearHeight + X * mNearWidth;
    nbl = nc - Y * mNearHeight - X * mNearWidth;

    //Corners of the far plane.
    ftr = fc + Y * mFarHeight + X * mFarWidth;
    ftl = fc + Y * mFarHeight - X * mFarWidth;
    fbr = fc - Y * mFarHeight + X * mFarWidth;
    fbl = fc - Y * mFarHeight - X * mFarWidth;

    //Whole planes can be computed using normal vector and the center point.
    //This is more efficient than use 3 points to calculate the plane.
    plane[TOP].setNormalPoint(((nc + Y * mNearHeight) - position) * X, nc + Y * mNearWidth);
    plane[BOTTOM].setNormalPoint(X * ((nc - Y * mNearHeight) - position), nc + Y * mNearWidth);
    plane[LEFT].setNormalPoint(((nc - X * mNearWidth) - position) * Y,nc-X*mNearWidth);
    plane[RIGHT].setNormalPoint(Y * ((nc + X * mNearWidth) - position), nc + X * mNearWidth);
    plane[NEAR].setNormalPoint(Z*-1, nc);
    plane[FAR].setNormalPoint(Z, fc);
}

bool CameraFP::testSphereFrustrum(CPoint3D center, float radius)
{
    float dist;

    for(int i=0; i < NPLANES; ++i)
    {
        dist = plane[i].distance(center);
        if (dist < -radius)
            return false;
        else if (dist < radius)
            return true;
    }
    return true;
}

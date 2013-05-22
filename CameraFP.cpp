#include "CameraFP.h"

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
    //Prevent division by zero.
    if (h > 0)
        mRatio = w/h;
    else
        mRatio = w/1.f;
    //FIXME: Angle was at 60 degrees.
    mAngle = 45.0f;
    if(w >= h)
        gluPerspective(mAngle, mRatio, Cnear, Cfar);
    else
        gluPerspective(mAngle , mRatio, Cnear, Cfar);
    CFrustrumManager::GetInstance()->setCamInternals(mAngle, mRatio, Cnear, Cfar);

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
    CFrustrumManager::GetInstance()->setCamDef(position, position + dir, up);
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




    //Whole planes can be computed using normal vector and the center point.
    //This is more efficient than use 3 points to calculate the plane.
//    plane[TOP].setNormalPoint(((nc + Y * mNearHeight) - position) * X, nc + Y * mNearHeight);
//    plane[BOTTOM].setNormalPoint(X * ((nc - Y * mNearHeight) - position), nc - Y * mNearHeight);

//    plane[LEFT].setNormalPoint(((nc - X * mNearWidth) - position) * Y,nc-X*mNearWidth);
//    plane[RIGHT].setNormalPoint(Y * ((nc + X * mNearWidth) - position), nc + X * mNearWidth);

//    plane[NEAR].setNormalPoint(Z*-1, nc);
//    plane[FAR].setNormalPoint(Z, fc);

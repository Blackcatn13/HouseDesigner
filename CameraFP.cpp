#include "CameraFP.h"
#include <cmath>

CameraFP::CameraFP()
{
    glMatrixMode(GL_POSITION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    Cnear = .1;
    Cfar = 1000;
    m_yaw = 0;
    m_pitch = 0;
    speedy = speedp = speedf = 1.0;
    position = CPoint3D(-5, 1.5, 0);
    dir = CPoint3D(0, 0, 0);
}

void CameraFP::setProjection(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w >= h)
        gluPerspective(60.0, w/h, Cnear, Cfar);
    else
        gluPerspective(60.0 , w/h, Cnear, Cfar);
}

void CameraFP::update()
{

    float yaw = toRad(m_yaw);
    float pitch = toRad(m_pitch);
    dir.x = cos(yaw) * cos(pitch);
    dir.y = sin(pitch);
    dir.z = sin(yaw) * cos(pitch);
    CPoint3D up(0,1,0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(position.x, position.y, position.z,
        position.x + dir.x, position.y + dir.y, position.z + dir.z,
        up.x, up.y, up.z);
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


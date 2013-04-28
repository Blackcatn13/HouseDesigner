#include "CameraFP.h"

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
    position = CPoint3D(0, 0, 0);
}

void CameraFP::setProjection(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w >= h)
        gluPerspective(45.0, 1.0 * w/h, Cnear, Cfar);
    else
        gluPerspective(45.0 * h/w, 1.0 * w/h, Cnear, Cfar);
}

void CameraFP::update()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    CPoint3D lookAt(cos(toRad(m_yaw))*cos(toRad(m_pitch)), sin(toRad(m_pitch)), sin(toRad(m_yaw))*cos(toRad(m_pitch)));
    qDebug() << "Position to look at originaly : " << lookAt.x << " , " << lookAt.y << " , " << lookAt.z;
    lookAt += position;
    CPoint3D up(-cos(toRad(m_yaw)) * sin(toRad(m_pitch)), cos(toRad(m_pitch)), -sin(toRad(m_yaw)) * sin(toRad(m_pitch)));
    qDebug() << "Position to look at : " << lookAt.x << " , " << lookAt.y << " , " << lookAt.z;
    gluLookAt(position.x, position.y, position.z,
        lookAt.x, lookAt.y, lookAt.z,
        up.x, up.y, up.z);

}

void CameraFP::move(float f, float s)
{
    CPoint3D addPos = CPoint3D();
    addPos.y = 0;
    addPos.x = f * cos(toRad(m_yaw)) + s*(cos(toRad(m_yaw) + PI*0.5));
    addPos.z = f * sin(toRad(m_yaw)) + s*(sin(toRad(m_yaw) + PI*0.5));

    addPos.Normalize();
    addPos * speedf;
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


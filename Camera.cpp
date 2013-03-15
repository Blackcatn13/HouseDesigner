#include "Camera.h"

Camera::Camera()
{
    // Initialize Modelview and Projection matrixes
    // (to set a clean state, even though this should be the default OpenGL values)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set default values for camera and projection
    R      = 2.5;
    angleh = 15;
    anglev = 35;
    Cnear   = .1;
    Cfar    = 500;
    currentView = PERSPECTIVE;
}

Camera::~Camera()
{
}

void Camera::setProjection(int w, int h, int i)
{
    switch(currentView)
    {
    case PERSPECTIVE:
        glViewport(0,0,w,h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        // Projection will be adapted to inverse aspect ratios
        if (w>=h)
            gluPerspective(60.0,1.0*w/h,Cnear,Cfar);
        else
            gluPerspective(60.0*h/w,1.0*w/h,Cnear,Cfar);
        break;
    case MULTIVIEW:
        switch(i){
        case 0:
            glViewport(0, h/2, w/2, h/2);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-1, 1, -1, 1, 0.1f, 1000);
            break;
        case 1:
            glViewport(w/2, h/2, w/2, h/2);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-1, 1, -1, 1, 0.1f, 1000);
            break;
        case 2:
            glViewport(0, 0, w/2, h/2);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-1, 1, -1, 1, 0.1f, 1000);
            break;
        case 3:
            glViewport(w/2, 0, w/2, h/2);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-1, 1, -1, 1, 0.1f, 1000);
            break;
        }
    }
}

void Camera::update(int camera_index)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if(currentView == PERSPECTIVE)
    {
        float anglex,angley;
        GLfloat cam[3],up[3];

        // Rad -> Deg
        anglex=angleh*PI/180;
        angley=anglev*PI/180;
        if(R<1.0) R=1.0;

        // Cam position and up-vector
        cam[0]=R*cos(anglex)*cos(angley);
        cam[1]=R*sin(anglex)*cos(angley);
        cam[2]=R*sin(angley);
        up[0]=-cos(anglex)*sin(angley);
        up[1]=-sin(anglex)*sin(angley);
        up[2]=cos(angley);

        // Set camera in OpenGL
        gluLookAt(cam[0],cam[1],cam[2],
                  0.0,0.0,0.0,
                  up[0],up[1],up[2]);
    }
    else
    {
        switch(camera_index)
        {
        case 0:
            gluLookAt(5.0, 0.0, 0.0,
                      0.0, 0.0, 0.0,
                      0.0, 0.0, 1.0);
            break;
        case 1:
            gluLookAt(0.0, -5.0, 0.0,
                      0.0, 0.0, 0.0,
                      0.0, 0.0, 1.0);
            break;
        case 2:
            gluLookAt(0.0, 0.0, 5.0,
                      0.0, 0.0, 0.0,
                      -1.0, 0.0, 0.0);
            break;
        case 3:
            gluLookAt(5.0, 5.0, 5.0,
                      0.0, 0.0, 0.0,
                      0.0, 0.0, 1.0);
            break;
        }
    }
}

void Camera::move(float ah, float av)
{
    if(currentView == PERSPECTIVE)
    {
        angleh += ah/2;
        anglev -= av/2;

        if(anglev>=360)	anglev=anglev-360;
        if(anglev<0)	anglev=anglev+360;
        if(angleh>=360)	angleh=angleh-360;
        if(angleh<0)	angleh=angleh+360;
    }
}

void Camera::setView(Views view)
{
    currentView = view;
}

Views Camera::getView()
{
    return currentView;
}

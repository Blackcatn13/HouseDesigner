#include "CameraPerspective.h"

CameraPerspective::CameraPerspective()
{
    // Initialize Modelview and Projection matrixes
    // (to set a clean state, even though this should be the default OpenGL values)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set default values for camera and projection
    R      = 25;
    angleh = 15;
    anglev = 35;
    Cnear   = .1;
    Cfar    = 500;
}

CameraPerspective::~CameraPerspective()
{
}

void CameraPerspective::setProjection(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Projection will be adapted to inverse aspect ratios
	if (w>=h)
		gluPerspective(60.0,1.0*w/h,Cnear,Cfar);
	else
		gluPerspective(60.0*h/w,1.0*w/h,Cnear,Cfar);
}

void CameraPerspective::update()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float anglex,angley;
    GLfloat cam[3],up[3];

    // Rad -> Deg
    anglex=angleh*PI/180;
    angley=anglev*PI/180;

    // Cam position and up-vector
    cam[0]=R*cos(anglex)*cos(angley);
    cam[1]=R*sin(anglex)*cos(angley);
    cam[2]=R*sin(angley);


    // Set camera in OpenGL
    gluLookAt(cam[0],cam[1],cam[2],
                0.0,0.0,0.0,
                0,1,0);
}

void CameraPerspective::move(float ah, float av)
{
    angleh += ah;
    anglev += av;
}

void CameraPerspective::AddDistance(float d)
{
    R += d;
    if(R < 1.0)
        R = 1.0;
}

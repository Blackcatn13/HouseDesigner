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
	currentView = ORTHOGONAL;
    orthoZoom = 2.5;
    orthoAngleH = 0;
    orthoAngleV = 0;
}

Camera::~Camera()
{
}

void Camera::setProjection(int w, int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	switch(currentView)
	{
	case PERSPECTIVE:
		// Projection will be adapted to inverse aspect ratios
		if (w>=h)
			gluPerspective(60.0,1.0*w/h,Cnear,Cfar);
		else
			gluPerspective(60.0*h/w,1.0*w/h,Cnear,Cfar);
		break;
	case ORTHOGONAL:
        glOrtho(-1 + orthoZoom, 1 - orthoZoom, -1 + orthoZoom, 1 - orthoZoom, -1, 3.5);
		break;
	}
}

void Camera::update()
{
    switch(currentView)
	{
	case PERSPECTIVE:
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
		//up[0]=-cos(anglex)*sin(angley);
		//up[1]=-sin(anglex)*sin(angley);
		//up[2]=cos(angley);
		up[0] = 0;
		up[1] = 1;
		up[2] = 0;

		// Set camera in OpenGL
		gluLookAt(cam[0],cam[1],cam[2],
					0.0,0.0,0.0,
					up[0],up[1],up[2]);
		break;
	case ORTHOGONAL:
        glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();
        glOrtho(-1 + orthoZoom, 1 - orthoZoom, -1 + orthoZoom, 1 - orthoZoom, -10, 50);

		glMatrixMode(GL_MODELVIEW);
	    glLoadIdentity();

        gluLookAt(-orthoAngleH, 1.0, orthoAngleV,
                  -orthoAngleH, 0.0, orthoAngleV,
                  -1.0, 0.0, 0.0);
        break;
	}
}

void Camera::move(float ah, float av)
{
    switch(currentView)
    {
    case PERSPECTIVE:
        angleh += ah/2;
        anglev -= av/2;

        if(anglev>=360)	anglev=anglev-360;
        if(anglev<0)	anglev=anglev+360;
        if(angleh>=360)	angleh=angleh-360;
        if(angleh<0)	angleh=angleh+360;
        break;
    case ORTHOGONAL:
        orthoAngleH += ah;
        orthoAngleV += av;
        break;
    }
}

void Camera::AddDistance(float d)
{
    switch(currentView)
    {
    case PERSPECTIVE:
        R += d;
        if(R < 1.0)
            R = 1.0;
        break;
    case ORTHOGONAL:
        orthoZoom += d;
        if(orthoZoom < 1.5)
            orthoZoom = 1.5;
        break;
    }
}

void Camera::setView(Views view)
{
    currentView = view;
}
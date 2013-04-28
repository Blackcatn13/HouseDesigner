#include "CameraOrtho.h"

CameraOrtho::CameraOrtho()
{
    // Initialize Modelview and Projection matrixes
    // (to set a clean state, even though this should be the default OpenGL values)
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set default values for camera and projection
    //FIXME: Set orthozoom to 2.5 again and orthoangles to 0.
    orthoZoom = -20;
    orthoAngleH = -2;
    orthoAngleV = -2;
}

CameraOrtho::~CameraOrtho()
{
}

void CameraOrtho::setProjection(int, int)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-0.1, 10 - orthoZoom, -0.1, 10 - orthoZoom, 0.1, 50);
    glMatrixMode(GL_MODELVIEW);
}

void CameraOrtho::update()
{
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(-0.1, 10 - orthoZoom, -0.1, 10 - orthoZoom, 0.1, 50);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    gluLookAt(orthoAngleH, 3.0, orthoAngleV,
                orthoAngleH, 0.0, orthoAngleV,
                1.0, 0.0, 0.0);
}

void CameraOrtho::move(float ah, float av)
{
    orthoAngleH += ah;
    orthoAngleV += av;
}

void CameraOrtho::AddDistance(float d)
{
    orthoZoom += d;
    if(orthoZoom >= 4)
        orthoZoom = 4;
    if(orthoZoom <= -20)
        orthoZoom = -20;
}

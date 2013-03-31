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
    orthoZoom = 2.5;
    orthoAngleH = 0;
    orthoAngleV = 0;
}

CameraOrtho::~CameraOrtho()
{
}

void CameraOrtho::setProjection(int, int)
{
    glOrtho(-1 + orthoZoom, 1 - orthoZoom, -1 + orthoZoom, 1 - orthoZoom, -1, 3.5);
}

void CameraOrtho::update()
{
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(-1 + orthoZoom, 1 - orthoZoom, -1 + orthoZoom, 1 - orthoZoom, -10, 50);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    gluLookAt(-orthoAngleH, 1.0, orthoAngleV,
                -orthoAngleH, 0.0, orthoAngleV,
                -1.0, 0.0, 0.0);
}

void CameraOrtho::move(float ah, float av)
{
    orthoAngleH += ah;
    orthoAngleV += av;
}

void CameraOrtho::AddDistance(float d)
{
    orthoZoom += d;
    if(orthoZoom < 1.5)
        orthoZoom = 1.5;
}
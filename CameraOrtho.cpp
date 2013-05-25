#include "CameraOrtho.h"
#include "Scenary.h"

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

void CameraOrtho::setProjection(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-0.1, 10 - orthoZoom, -0.1, 10 - orthoZoom, 0.01, 1000);
}

void CameraOrtho::update()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    int height = (CScenary::getInstance()->getCurrentFloor()+ 1) * 3;
    gluLookAt(orthoAngleH, height, orthoAngleV,
                orthoAngleH, 0.0, orthoAngleV,
                1.0, 0.0, 0.0);
}

void CameraOrtho::move(float ah, float av, bool)
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
    setProjection(0,0);
}

#include "Illumination.h"

Illumination::Illumination()
{
    // Init illumination
    // (setting it for fixed functiony, will be bypassed by the shaders if active)
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    // default components for global illumination
    pos[0] = 0.0; pos[1] = 0.0; pos[2] = 1.0; pos[3] = 1.0;
    dif[0] = 0.5; dif[1] = 0.5; dif[2] = 0.5; dif[3] = 1.0;
    amb[0] = 0.0; amb[1] = 0.0; amb[2] = 0.0; amb[3] = 1.0;
    spe[0] = 0.0; spe[1] = 0.0; spe[2] = 0.0; spe[3] = 1.0;

}

Illumination::~Illumination()
{
}

void Illumination::update()
{

    glDisable(GL_LIGHT0);
    glLightfv(GL_LIGHT0,GL_POSITION, pos);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,  dif);
    glLightfv(GL_LIGHT0,GL_SPECULAR, spe);
    glLightfv(GL_LIGHT0,GL_AMBIENT,  amb);
    glEnable(GL_LIGHT0);

}

void Illumination::draw()
{
    // Turn light off for light prop.
    // This light trick will only work on fixed function.
    // You are free to implement specific action for your
    // custom shaders!
    glDisable(GL_LIGHTING);

    glPushMatrix();
    glColor3f(0.8,0.8,0.0);
    glTranslatef(pos[0],pos[1],pos[2]);
    glutSolidSphere(.1,10,10);
    glPopMatrix();

    glEnable(GL_LIGHTING);
}

void Illumination::move(float ah, float av)
{
    pos[0] += ah;
    pos[1] += av;
}

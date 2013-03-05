#ifndef _UTIL_H
#define _UTIL_H

#define PI 3.14159

#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <GLUT/glut.h>
#else
    #ifdef _WIN32
        #include <windows.h>
    #endif

    #include <GL/glew.h>
    #include <GL/gl.h>
    #include <GL/glu.h>

    #ifdef FREEGLUT
        #include <GL/freeglut.h>
    #else
        #include <GL/glut.h>
    #endif
#endif

#include <math.h>
#include <QDebug>

struct Point3D{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};
struct Point2D{
    GLfloat x;
    GLfloat y;
};

enum Views {PERSPECTIVE, MULTIVIEW};
#endif  /* _UTIL_H */

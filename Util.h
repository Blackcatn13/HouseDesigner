#ifndef _UTIL_H
#define _UTIL_H

#include "Point3D.h"
#include <string>

using namespace std;

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

struct Point2D{
    GLfloat x;
    GLfloat y;
};

struct ModelInfo{
    CPoint3D position;
    CPoint3D rotation;
    CPoint3D scale;
    string modelName;
    string textureName;
};

enum Views {PERSPECTIVE, MULTIVIEW};
enum Modes {EDITOR_2D, EXPLORER, EXPLORER_ISO};
#endif  /* _UTIL_H */

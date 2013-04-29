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


#define INIT_WIDTH 800
#define INIT_HEIGHT 600

enum Views {PERSPECTIVE, ORTHOGONAL, FP};
enum Modes {EDITOR_2D, EXPLORER, EXPLORER_ISO};
enum Types {WALL, OBJECT, NOTHING};

struct Point2D{
    GLfloat x;
    GLfloat y;
    
    Point2D()
    {
        x = 0.0;
        y = 0.0;
    }

    Point2D(float nx, float ny)
    {
        x = nx;
        y = ny;
    }
};

struct ModelInfo{
    CPoint3D position;
    CPoint3D rotation;
    CPoint3D scale;
    string modelName;
    string textureName;
    Types type;
    float height;
    float width;

    ModelInfo()
    {
        position = CPoint3D();
        rotation = CPoint3D();
        scale = CPoint3D();
        modelName = "";
        textureName = "";
        type = NOTHING;
        height = 0;
        width = 0;
    }

    ModelInfo(CPoint3D pos, CPoint3D rot, CPoint3D sc, string name, string texture, Types t, float h, float w)
    {
        position = pos;
        rotation = rot;
        scale = sc;
        modelName = name;
        textureName = texture;
        type = t;
        height = h;
        width = w;
    }

    bool operator==(const ModelInfo &mi) const
    {
        if(type != mi.type)
            return false;
        if(modelName != mi.modelName)
            return false;
        if(position != mi.position)
            return false;
        if(rotation != mi.rotation)
            return false;
        return true;
    }
    // Modificar constructor per tal de poder pasarli parametres i segons el tipus de model
    // fdeixarne alguns com a predefinits.
    // Override metode ==
};


#endif  /* _UTIL_H */

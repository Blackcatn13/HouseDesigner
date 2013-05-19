#ifndef PLANE_H
#define PLANE_H

#include "Point3D.h"
#include "Util.h"

class CPlane
{
public:
    CPlane(void);
    //Set plane with 3 points.
    void set3Points (CPoint3D v1, CPoint3D v2, CPoint3D v3);
    //Set plane with Normal and a point.
    void setNormalAndPoint(CPoint3D normal, CPoint3D point);
    //Set plane using Ax + By + Cz + D equation.
    void setCoefficients(float a, float b, float c, float d);
    float distance(CPoint3D point);

private:
    CPoint3D mNormal, mPoint;
    float mD;

};

#endif // PLANE_H

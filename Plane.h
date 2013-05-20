#ifndef PLANE_H
#define PLANE_H

#include "Point3D.h"
#include "Util.h"

class CPlane
{
public:
    CPlane(void);
    void set3Point(CPoint3D p1, CPoint3D p2, CPoint3D p3);
    //Set plane with Normal and a point.
    void setNormalPoint(CPoint3D normal, CPoint3D point);
    //Calculate distance between plane and a given point.
    float distance(CPoint3D point);

private:
    CPoint3D mNormal, mPoint;
    float mD;

};

#endif // PLANE_H

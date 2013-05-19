#ifndef PLANE_H
#define PLANE_H

#include "Point3D.h"
#include "Util.h"

class CPlane
{
public:
    CPlane(void);
    //Set plane with Normal and a point.
    void setNormalPoint(CPoint3D normal, CPoint3D point);
    //Calculate distance between plane and a given point.
    float distance(CPoint3D point);

private:
    CPoint3D mNormal, mPoint;
    float mD;

};

#endif // PLANE_H

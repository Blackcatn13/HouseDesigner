#include "Plane.h"

CPlane::CPlane()
{
}

void CPlane::setNormalPoint(CPoint3D normal, CPoint3D point)
{
    mNormal = normal;
    mPoint = point;
    //Calculate angle between normal and p2 vectors
    mD = mNormal.Dot(point)*-1;
}

float CPlane::distance(CPoint3D point)
{
    //Return distance (d is negative + distance p positive).
    return mD + acos(mNormal.Dot(point)/(mNormal.Norma()*point.Norma()));
}

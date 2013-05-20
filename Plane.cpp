#include "Plane.h"

CPlane::CPlane()
{
}

void CPlane::set3Point(CPoint3D p1, CPoint3D p2, CPoint3D p3)
{
    CPoint3D aux1, aux2;
    aux1 = p1 - p2;
    aux2 = p3 - p2;
    mNormal = aux2*aux1;

    mNormal.Normalize();
    mD = mNormal.Dot(p2)*-1;
}

void CPlane::setNormalPoint(CPoint3D normal, CPoint3D point)
{
    mNormal = normal;
    mNormal.Normalize();
    mPoint = point;
    //Calculate dot product between normal and p2 vectors
    mD = mNormal.Dot(point)*-1;
}

float CPlane::distance(CPoint3D point)
{
    //Return distance (d is negative + distance p positive).
    return mD + mNormal.Dot(point);
}

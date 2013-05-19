#include "Plane.h"

CPlane::CPlane()
{
}

void CPlane::set3Points(CPoint3D p1, CPoint3D p2, CPoint3D p3)
{
    CPoint3D aux, aux1;
    //Calculate vectors.
    aux = p1 - p2;
    aux1 = p3 - p2;

    mNormal = aux1 * aux;
    mNormal.Normalize();
    //Calculate angle between normal and p2 vectors.
    mD = acos(mNormal.Dot(p2)/(mNormal.Norma()*p2.Norma()))*-1;
}

void CPlane::setNormalAndPoint(CPoint3D normal, CPoint3D point)
{
    mNormal = normal;
    mPoint = point;
    //Calculate angle between normal and p2 vectors
    mD = acos(mNormal.Dot(point)/(mNormal.Norma()*point.Norma()))*-1;
}

float CPlane::distance(CPoint3D point)
{
    //Return distance (d is negative + distance p positive).
    return mD + acos(mNormal.Dot(point)/(mNormal.Norma()*point.Norma()));
}

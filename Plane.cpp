/*
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
*/
// Plane.cpp
//
//////////////////////////////////////////////////////////////////////

#include "Plane.h"
#include <stdio.h>


Plane::Plane( Vec3 &v1,  Vec3 &v2,  Vec3 &v3) {

    set3Points(v1,v2,v3);
}


Plane::Plane() {}

Plane::~Plane() {}


void Plane::set3Points( Vec3 v1,  Vec3 v2,  Vec3 v3) {


    Vec3 aux1, aux2;

    aux1 = v1 - v2;
    aux2 = v3 - v2;

    normal = aux2 * aux1;

    normal.normalize();
    point.copy(v2);
    d = -(normal.innerProduct(point));
}

void Plane::setNormalAndPoint(Vec3 &normal, Vec3 &point) {

    this->normal.copy(normal);
    this->normal.normalize();
    d = -(this->normal.innerProduct(point));
}

void Plane::setCoefficients(float a, float b, float c, float d) {

    // set the normal vector
    normal.set(a,b,c);
    //compute the lenght of the vector
    float l = normal.length();
    // normalize the vector
    normal.set(a/l,b/l,c/l);
    // and divide d by th length as well
    this->d = d/l;
}




float Plane::distance(Vec3 &p) {

    return (d + normal.innerProduct(p));
}

void Plane::print() {

    printf("Plane(");normal.print();printf("# %f)",d);
}

#include "Point3D.h"


CPoint3D::CPoint3D(void)
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}


CPoint3D::~CPoint3D(void)
{
}

CPoint3D CPoint3D::operator*(const CPoint3D p)
{
    return CPoint3D((y*p.z-z*p.y),(z*p.x-x*p.z),(x*p.y-y*p.x));
}

CPoint3D CPoint3D::operator+(const CPoint3D p)
{
    return CPoint3D(x + p.x, y + p.y, z + p.z);
}

CPoint3D & CPoint3D::operator+=(const CPoint3D p)
{
    x += p.x;
    y += p.y;
    z += p.z;
    return *this;
}

CPoint3D CPoint3D::operator-(const CPoint3D p)
{
    return CPoint3D(x - p.x, y - p.y, z - p.z);
}

CPoint3D & CPoint3D::operator=(const CPoint3D p)
{
    x = p.x;
    y = p.y;
    z = p.z;
    return *this;
}

bool CPoint3D::operator==(const CPoint3D p)
{
    return (x==p.x && y == p.y && z == p.z);
}

#include "Point3D.h"
#include <cmath>

CPoint3D::CPoint3D(void)
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}


CPoint3D::~CPoint3D(void)
{
}

CPoint3D::CPoint3D(float nx, float ny, float nz)
{
    x = nx;
    y = ny;
    z = nz;
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

bool CPoint3D::operator==(const CPoint3D &p) const
{
    return (x==p.x && y == p.y && z == p.z);
}

bool CPoint3D::operator!=(const CPoint3D &p) const
{
    return !(x==p.x && y == p.y && z == p.z);
}

void CPoint3D::Normalize()
{
    float mod = sqrt(x*x + y*y + z*z);
    x /= mod;
    y /= mod;
    z /= mod;
}

float CPoint3D::Norma()
{
    return sqrt(x*x + y*y + z*z);
}

float CPoint3D::Dot(const CPoint3D p)
{
    return x*p.x + y*p.y + z*p.z;
}

CPoint3D CPoint3D::operator*(const float val)
{
    return CPoint3D(x*val, y*val, z*val);
}

CPoint3D CPoint3D::operator/(const float val)
{
    return CPoint3D(x/val, y/val, z/val);
}

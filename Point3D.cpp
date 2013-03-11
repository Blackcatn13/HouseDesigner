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
    return CPoint3D();
}

CPoint3D CPoint3D::operator+(const CPoint3D p)
{
    return CPoint3D();
}

CPoint3D & CPoint3D::operator+=(const CPoint3D p)
{
    return CPoint3D();
}

CPoint3D CPoint3D::operator-(const CPoint3D p)
{
    return CPoint3D();
}

CPoint3D & CPoint3D::operator=(const CPoint3D p)
{
    return CPoint3D();
}

bool CPoint3D::operator==(const CPoint3D p)
{
    return false;
}

#include "Plane.h"

CPlane::CPlane()
{
}


void CPlane::set3Points( CPoint3D p1,  CPoint3D p2,  CPoint3D p3)
{
    CPoint3D a1, a2;
    a1 = p1 - p2;
    a2 = p3 - p2;

    m_normal = a2 * a1;
    m_normal.Normalize();
    m_point = p2;
    m_dist = m_normal.Dot(m_point)*-1;
}

void CPlane::setNormalAndPoint(CPoint3D normal, CPoint3D point)
{
    m_normal = normal;
    m_normal.Normalize();
    m_dist = m_normal.Dot(point)-1;
}




float CPlane::distance(CPoint3D p)
{
    return (m_dist + m_normal.Dot(p));
}

#ifndef _CPlane_
#define _CPlane_

#include "Point3D.h"

class CPoint3D;

class CPlane
{

public:

    CPlane(void);
    void set3Points(CPoint3D p1,  CPoint3D p2,  CPoint3D p3);
    void setNormalAndPoint(CPoint3D normal, CPoint3D point);
    float distance(CPoint3D p);
private:
    CPoint3D m_normal, m_point;
    float m_dist;
};


#endif

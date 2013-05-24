#ifndef FRUSTRUMMANAGER_H
#define FRUSTRUMMANAGER_H

#include "Plane.h"
#include "Point3D.h"

class CPoint3D;
class Plane;

class CFrustrumManager
{
public:
    enum {OUTSIDE, INTERSECT, INSIDE};
    CPlane pl[6];

    static CFrustrumManager* GetInstance();
    void setCamInternals(float angle, float ratio, float nearD, float farD);
    void setCamDef(CPoint3D p, CPoint3D l, CPoint3D u);
    bool sphereInFrustum(CPoint3D p, float radius);


private:
    enum {
            TOP = 0,
            BOTTOM,
            LEFT,
            RIGHT,
            NEARP,
            FARP
        };
    CFrustrumManager();
    ~CFrustrumManager();
    static CFrustrumManager*   m_FrustrumManager;

    CPoint3D ntl,ntr,nbl,nbr,ftl,ftr,fbl,fbr;
    float nearD, farD, ratio, angle,tang;
    float nw,nh,fw,fh;
};

#endif // FRUSTRUMMANAGER_H

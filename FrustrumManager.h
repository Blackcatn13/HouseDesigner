#ifndef FRUSTRUMMANAGER_H
#define FRUSTRUMMANAGER_H

#include "Plane.h"
#include "Vec3.h"

class Vec3;
class Plane;

class CFrustrumManager
{
public:
    enum {OUTSIDE, INTERSECT, INSIDE};
    Plane pl[6];

    static CFrustrumManager* GetInstance();
    void setCamInternals(float angle, float ratio, float nearD, float farD);
    void setCamDef(Vec3 p, Vec3 l, Vec3 u);
    bool sphereInFrustum(Vec3 p, float raio);


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

    Vec3 ntl,ntr,nbl,nbr,ftl,ftr,fbl,fbr;
    float nearD, farD, ratio, angle,tang;
    float nw,nh,fw,fh;
};

#endif // FRUSTRUMMANAGER_H

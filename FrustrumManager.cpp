#include "FrustrumManager.h"
#include "math.h"

CFrustrumManager *CFrustrumManager::m_FrustrumManager = 0;

#define ANG2RAD 3.14159265358979323846/180.0

CFrustrumManager::CFrustrumManager()
{
}

void CFrustrumManager::setCamInternals(float angle, float ratio, float nearD, float farD)
{
    this->ratio = ratio;
    this->angle = angle;
    this->nearD = nearD;
    this->farD = farD;

    tang = (float)tan(angle* ANG2RAD * 0.5) ;
    nh = nearD * tang;
    nw = nh * ratio;
    fh = farD  * tang;
    fw = fh * ratio;
}

void CFrustrumManager::setCamDef(CPoint3D p, CPoint3D l, CPoint3D u)
{
    CPoint3D dir,nc,fc,X,Y,Z;

    Z = p - l;
    Z.Normalize();

    X = u * Z;
    X.Normalize();

    Y = Z * X;

    nc = p - Z * nearD;
    fc = p - Z * farD;

    ntl = nc + Y * nh - X * nw;
    ntr = nc + Y * nh + X * nw;
    nbl = nc - Y * nh - X * nw;
    nbr = nc - Y * nh + X * nw;

    ftl = fc + Y * fh - X * fw;
    ftr = fc + Y * fh + X * fw;
    fbl = fc - Y * fh - X * fw;
    fbr = fc - Y * fh + X * fw;

    pl[TOP].set3Points(ntr,ntl,ftl);
    pl[BOTTOM].set3Points(nbl,nbr,fbr);
    pl[LEFT].set3Points(ntl,nbl,fbl);
    pl[RIGHT].set3Points(nbr,ntr,fbr);
    pl[NEARP].set3Points(ntl,ntr,nbr);
    pl[FARP].set3Points(ftr,ftl,fbl);
}

bool CFrustrumManager::sphereInFrustum(CPoint3D p, float radius)
{
        float distance;

        for(int i=0; i < 6; i++) {
            distance = pl[i].distance(p);
            if (distance < -radius)
                return false;
        }
    return true;
}

CFrustrumManager* CFrustrumManager::GetInstance()
{
    if(m_FrustrumManager == 0)
        m_FrustrumManager = new CFrustrumManager();
    return m_FrustrumManager;
}

#ifndef POINT3D_H
#define POINT3D_H

class CPoint3D
{
public:
    CPoint3D(void);
    CPoint3D(float nx, float ny, float nz);
    ~CPoint3D(void);
    void Normalize();
    CPoint3D operator+(const CPoint3D p);
    CPoint3D operator-(const CPoint3D p);
    CPoint3D operator*(const CPoint3D p);
    CPoint3D operator*(const float val);
    CPoint3D &operator=(const CPoint3D p);
    CPoint3D &operator+=(const CPoint3D p);
    bool operator==(const CPoint3D &p) const;
    bool operator!=(const CPoint3D &p) const;
    float x, y, z;
};

#endif

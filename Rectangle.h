#include "Model.h"

#pragma once

class CPoint3D;

class CRectangle : public CModel
{
public:
    CRectangle(void);
    CRectangle(CPoint3D p, float h, float w);
    CRectangle(CPoint3D p, float w);
    ~CRectangle(void);

};


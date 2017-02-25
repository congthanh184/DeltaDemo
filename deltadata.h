#ifndef DELTADATA_H
#define DELTADATA_H

#include "QtGlobal"
#include "vector3.h"

// trigonometric constants
const float sqrt3 = sqrt(3.0);
const float sin120 = sqrt3/2.0;
const float cos120 = -0.5;
const float tan60 = sqrt3;
const float sin30 = 0.5;
const float tan30 = 1/sqrt3;

class DeltaData
{
private:
    Vector3 baseVertex[3], hipVertex[3];
    Vector3 kneeVertex[3], ankleVertex[3];
    Vector3 eeVertex[3];
    Vector3 eePos;
    float   theta[3];
    float   f, e, rf, re, rBase, rEE;

public:
    DeltaData();
    DeltaData( float f, float e, float rBase, float rEE, float rf, float re);     // overload

    Vector3* getDeltaBaseVertex();
    Vector3* getDeltaEEVertex();
    Vector3* getDeltaLegVertex(quint8 n);
};

#endif // DELTADATA_H

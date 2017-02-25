#ifndef DELTA_H
#define DELTA_H

#include <QObject>
#include "vector3.h"
#include <QGLWidget>

// trigonometric constants
const float sqrt3 = sqrt(3.0);
const float sin120 = sqrt3/2.0;
const float cos120 = -0.5;
const float tan60 = sqrt3;
const float sin30 = 0.5;
const float cos30 = sqrt(3)/2;
const float tan30 = 1/sqrt3;

class QGLWidget;

class DeltaParameter
{
public:
    // variable declare
    Vector3 baseVertex[3], hipVertex[3];
    Vector3 kneeVertex[3], ankleVertex[3];
    Vector3 eeVertex[3];
    Vector3 eePos;
    float   theta[3];
    float   f, e, rf, re, rBase, rEE;
};

class Delta : public QGLWidget
{
    Q_OBJECT
private:    
    // variable declare
    DeltaParameter  *myDelta;
    DeltaParameter *testDelta;

    // function declare
    Vector3 Rotate120( Vector3 );
    Vector3 Rotate240( Vector3 );
    float   r2( float );
    void    SetEEParam( DeltaParameter *data, Vector3 dstPos);
    uint8_t IK_Find_Angles( float x, float y, float z, DeltaParameter *src_dbot, DeltaParameter *d_bot);
    uint8_t FK_Find_Position( float theta1, float theta2, float theta3, DeltaParameter *src_dbot, DeltaParameter *d_bot);

public:
    explicit Delta(QGLWidget *parent = 0);
    Delta( float f, float e, float rBase, float rEE, float rf, float re);     // overload
    void Draw();
    void Clone( DeltaParameter );    
    float GetThetaAngle( uint8_t );
    uint8_t Set_EE_Position(Vector3 dstEEPos, float* thetaOutput, uint8_t update);
    uint8_t Set_Hips_Angles(Vector3* dstEEPos, float* theta, uint8_t update);
signals:
    void UpdateDParam( DeltaParameter );
public slots:

};

#endif // DELTA_H

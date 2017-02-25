#include "delta.h"
#include <QDebug>
#include <QTimerEvent>

//#define DEBUG_CALC_VERTEX_BASE
//#define DEBUG_CALC_IK_DELTA
//#define DEBUG_CALC_FK_DELTA

Delta::Delta(QGLWidget *parent) :
//    QObject(parent),
    QGLWidget(parent)
{
    myDelta = new DeltaParameter();
    testDelta = new DeltaParameter();
}
/****************************************************************************
  Du lieu vao la rBase va rEE, suy ra f/2 = rBase/tan30, tinh ra dc 2 dinh cua Base
  (song song voi Ox) va 1 nam tren 0y. Va tinh dc toa do cua 3 hip.

  rBase and rEE are inputs which are radius of Base and radius of End plate, 
  f/2 = rBase/tan30, initilize the model with 3 vertices of the base ( 2 of them 
  parallel with axis Ox, the last one on axis Oy), and coordinates of 3 hips.
*****************************************************************************/
Delta::Delta(float f, float e, float rBase, float rEE, float rf, float re){
    // init delta data
    myDelta = new DeltaParameter();
    testDelta = new DeltaParameter();

    myDelta->rf = rf;
    myDelta->re = re;

    if ( f == 0 ) {
        myDelta->rBase = rBase;
        myDelta->rEE = rEE;
        myDelta->f = 2 * rBase / tan30;
        myDelta->e = 2 * rEE / tan30;
    }
    else {
        myDelta->f = f;
        myDelta->e = e;
        myDelta->rBase = f * 0.5 * tan30;
        myDelta->rEE = e * 0.5 * tan30;
    }

    // 3 coordinates of base
    rBase = myDelta->rBase;
    myDelta->baseVertex[0].Set( -rBase/tan30, -rBase, 0);
    myDelta->baseVertex[1].Set(  rBase/tan30, -rBase, 0);
    myDelta->baseVertex[2].Set( 0, rBase/sin30 , 0);

    // 3 coordinates of hip
    myDelta->hipVertex[0].Set( 0, -rBase, 0);
    myDelta->hipVertex[1] = Rotate120( myDelta->hipVertex[0]);
    myDelta->hipVertex[2] = Rotate240( myDelta->hipVertex[0]);

    #ifdef DEBUG_CALC_VERTEX_BASE
        for (int i = 0; i < 3; i++){
            qDebug() << myDelta->baseVertex[i].x << myDelta->baseVertex[i].y << myDelta->baseVertex[i].z;
            qDebug() << myDelta->hipVertex[i].x << myDelta->hipVertex[i].y << myDelta->hipVertex[i].z;
        }
    #endif
}
/****************************************************************************/
/*  function Set_EE_Position : tinh goc quay theta tuong ung voi vi tri EE  */
/*        input : Vector3 - Toa do moi cua EE                               */
/*        output: float* theta-Goc quay cua dong co tuong ung voi truc toa  */
/*                do cua base                                               */
/*        update = 1 : cap nhat lai data cho myDelta                        */
/*        return 0 neu tao do nam trong vung hoat dong                      */
/*        return 1 neu tao do nam ngoai vung hoat dong                      */
/****************************************************************************/
/****************************************************************************/
/*  function Set_EE_Position : update configuration from new position of EE */
/*        input : Vector3 - coordinates of new position EE                  */
/*        output: float* theta - the angle of 3 legs                        */
/*        update = 1 : flag update myDelta with new config                  */
/*        return 0 if EE position is in working zone                        */
/*        return 1 otherwise                                                */
/****************************************************************************/
uint8_t Delta::Set_EE_Position(Vector3 dstEEPos, float* thetaOutput, uint8_t update) {
    if ( IK_Find_Angles( dstEEPos.x, dstEEPos.y, dstEEPos.z, myDelta, testDelta) == 0 ) {
        if (thetaOutput != 0)
        {
            thetaOutput[0] = testDelta->theta[0];
            thetaOutput[1] = testDelta->theta[1];
            thetaOutput[2] = testDelta->theta[2];
        }

        if (update) {
            *myDelta = *testDelta;
            UpdateDParam( *myDelta );
        }
    }
    else {
        return 1;
    }    
    return 0;
}
/****************************************************************************/
/*  function Set_Hips_Angles : xac dinh vi tri EE tuong ung voi goc quay dc */
/*        input : array theta - Goc quay cua dong co                        */
/*        output: vector3 - vi tri EE moi                                   */
/*        update = 1 : cap nhat lai data cho myDelta                        */
/*        return 0 neu tao do nam trong vung hoat dong                      */
/*        return 1 neu tao do nam ngoai vung hoat dong                      */
/****************************************************************************/
/****************************************************************************/
/*  function Set_Hips_Angles :  forward kinematic find EE based on          */
/*                              config of legs                              */
/*        input : array theta - config of legs                              */
/*        output: vector3 - new position of EE                              */
/*        update = 1 : flag update myDelta with new config                  */
/*        return 0 if EE position is in working zone                        */
/*        return 1 otherwise                                                */
/****************************************************************************/
uint8_t Delta::Set_Hips_Angles(Vector3* dstEEPos, float* theta, uint8_t update) {
    if ( FK_Find_Position( theta[0], theta[1], theta[2], myDelta, testDelta) == 0 ) {        
        if (dstEEPos != 0)
            *dstEEPos = myDelta->eePos;
        if (update) {
            *myDelta = *testDelta;
            UpdateDParam( *myDelta );
        }
    }
    else {
        return 1;
    }
    return 0;
}
/****************************************************************************
  function IK_Find_Angles : tinh cac goc theta tuong ung voi toa do x, y, z
    return 0 neu tao do nam trong vung hoat dong
    return 1 neu tao do nam ngoai vung hoat dong
    result_array la
*****************************************************************************/
/****************************************************************************
  function  IK_Find_Angles : implement inverse kinematics, calculate angle from 
                            x, y, z
            return 0 if EE position is in working zone                        
            return 1 otherwise                                                
/****************************************************************************/
uint8_t Delta::IK_Find_Angles(float x, float y, float z, DeltaParameter* src_dbot, DeltaParameter *d_bot) {
    // init result data
    *d_bot = *src_dbot;
    SetEEParam( d_bot, Vector3(x, y, z));

    Vector3 dstOriginPos = d_bot->eePos;

    for ( uint8_t i = 0; i<3; i++){
        if ( i == 1)
            // Xoay goc toa do 120 xac dinh toa do EE theo he truc moi
            dstOriginPos = Rotate240(d_bot->eePos);
        else if (i == 2)
            // Xoay goc toa do 240 xac dinh toa do EE theo he truc moi
            dstOriginPos = Rotate120(d_bot->eePos);

        // Xac dinh toa do diem ankles C1( xEE, yEE - rEE, zEE) => C1'( 0, yEE - rEE, zEE)
        dstOriginPos.y -= d_bot->rEE;
        // Tinh do dai doan re' = re^2 - xEE
        float re1_sqr = r2(d_bot->re) - r2(dstOriginPos.x);
        float re1 = sqrt(re1_sqr);
        // Tinh khoang cach tu hip D1 toi C1'
        float length_sqr = r2( d_bot->hipVertex[0].y - dstOriginPos.y) + r2(dstOriginPos.z);
        float length = sqrt(length_sqr);
        // Kiem tra EE position co nam trong vung lam viec hay ko
        if ( (length > (re1 + d_bot->rf)) || (length < abs(re1 - d_bot->rf)) ){
            qDebug() << "Out of bound";
            return 1;
        }
        // Tim alpha va h
        float alpha = - (length_sqr + r2(d_bot->rf) - re1_sqr) / (2 * length);
        float h = - sqrt ( r2(d_bot->rf) - r2(alpha) );

        // Xac dinh goc quay cua he toa do gan voi duong thang noi tu hip D1 toi C1'
        float cgamma = -dstOriginPos.z / length;
        float sgamma = ( dstOriginPos.y + d_bot->rBase) / length;

        float tempY = cgamma * h - sgamma * alpha;
        float tempZ = sgamma * h + cgamma * alpha;

        d_bot->theta[i] = atan2( tempZ, tempY);        // rad

        d_bot->kneeVertex[i].Set( 0, tempY + d_bot->hipVertex[0].y, tempZ);
        if ( i == 1)
            d_bot->kneeVertex[i] = Rotate120( d_bot->kneeVertex[i]);
        else if (i == 2)
            d_bot->kneeVertex[i] = Rotate240( d_bot->kneeVertex[i]);
    }
#ifdef DEBUG_CALC_IK_DELTA
        float angleOfServo;
        float length;
        uint8_t i;
        qDebug() << "**** Inverse Kinematics ****";

        qDebug() << "Theta (degrees - relative to Base's coordinates)";
        for ( i = 0; i<3; i++){
            float angleOfServo;
//            if ( d_bot->theta[i] > 0 )
//                angleOfServo = 180 - d_bot->theta[i];
//            else
//                angleOfServo = d_bot->theta[i] + 180;
            qDebug() << "Theta[" << i << "] = " << d_bot->theta[i] * RAD2DEG;
        }

        qDebug() << "Knee Position";
        for (i = 0; i<3; i++)
        {
            qDebug() << d_bot->kneeVertex[i].x
                     << d_bot->kneeVertex[i].y
                     << d_bot->kneeVertex[i].z;
        }

        qDebug() << "re Length";
        for (i = 0; i<3; i++) {
            length = sqrt( r2(d_bot->kneeVertex[i].x - d_bot->ankleVertex[i].x)
                           + r2(d_bot->kneeVertex[i].y - d_bot->ankleVertex[i].y)
                           + r2(d_bot->kneeVertex[i].z - d_bot->ankleVertex[i].z));
            qDebug() << "re length" << i << length;
        }

        qDebug() << "rf Length";
        for (i = 0; i<3; i++) {
            length = sqrt( r2(d_bot->kneeVertex[i].x - d_bot->hipVertex[i].x)
                           + r2(d_bot->kneeVertex[i].y - d_bot->hipVertex[i].y)
                           + r2(d_bot->kneeVertex[i].z - d_bot->hipVertex[i].z));
            qDebug() << "rf length" << i << length;
        }
#endif
    return 0;
}
/****************************************************************************
  function FK_Find_Position : tinh toa do end effector tuong ung voi goc theta
    return 0 neu tao do nam trong vung hoat dong
    return 1 neu tao do nam ngoai vung hoat dong
    return d_bot : thong tin ve vi tri cac co cau
*****************************************************************************/
/****************************************************************************
  function FK_Find_Position : implement inverse kinematics 
    return 0 if EE position is in working zone                        
    return 1 otherwise                                                
    return d_bot : copy of new delta model
*****************************************************************************/
uint8_t Delta::FK_Find_Position(float theta1, float theta2, float theta3, DeltaParameter* src_dbot, DeltaParameter *d_bot){
    // init d_bot
    *d_bot = *(src_dbot);
    d_bot->theta[0] = theta1;
    d_bot->theta[1] = theta2;
    d_bot->theta[2] = theta3;

    // calculate knee 1
    d_bot->kneeVertex[0].x = 0;
    d_bot->kneeVertex[0].y = d_bot->rf * cos(theta1) - d_bot->rBase;
    d_bot->kneeVertex[0].z = d_bot->rf * sin(theta1);

    // calculate knee 2
    float k = - d_bot->rf * cos(theta2) + d_bot->rBase;
    d_bot->kneeVertex[1].x = k * cos30;
    d_bot->kneeVertex[1].y = k * sin30;
    d_bot->kneeVertex[1].z = d_bot->rf * sin(theta2);

    // calculate knee 2
    k = - d_bot->rf * cos(theta3) + d_bot->rBase;
    d_bot->kneeVertex[2].x = - k * cos30;
    d_bot->kneeVertex[2].y = k * sin30;
    d_bot->kneeVertex[2].z = d_bot->rf * sin(theta3);

    // calc x', y', z'
    float y1 = d_bot->rEE + d_bot->kneeVertex[0].y;
    float z1 = d_bot->kneeVertex[0].z;

    float x2 = - sin120 * d_bot->rEE + d_bot->kneeVertex[1].x;
    float y2 = cos120 * d_bot->rEE + d_bot->kneeVertex[1].y;
    float z2 = d_bot->kneeVertex[1].z;

    float x3 = sin120 * d_bot->rEE + d_bot->kneeVertex[2].x;
    float y3 = cos120 * d_bot->rEE + d_bot->kneeVertex[2].y;
    float z3 = d_bot->kneeVertex[2].z;

    float dnm = (y2-y1)*x3-(y3-y1)*x2;

    float w1 = y1*y1 + z1*z1;
    float w2 = x2*x2 + y2*y2 + z2*z2;
    float w3 = x3*x3 + y3*y3 + z3*z3;

    // x = (a1*z + b1)/dnm
    float a1 = (z2-z1)*(y3-y1)-(z3-z1)*(y2-y1);
    float b1 = -((w2-w1)*(y3-y1)-(w3-w1)*(y2-y1))/2.0;

    // y = (a2*z + b2)/dnm;
    float a2 = -(z2-z1)*x3+(z3-z1)*x2;
    float b2 = ((w2-w1)*x3 - (w3-w1)*x2)/2.0;

    // a*z^2 + b*z + c = 0
    float a = a1*a1 + a2*a2 + dnm*dnm;
    float b = 2*(a1*b1 + a2*(b2-y1*dnm) - z1*dnm*dnm);
    float c = (b2-y1*dnm)*(b2-y1*dnm) + b1*b1 + dnm*dnm*(z1*z1 - r2(d_bot->re));

    // discriminant
    float d = b*b - (float)4.0*a*c;

    if (d < 0)
        return 1; // non-existing point

    float z0 = -(float)0.5*(b+sqrt(d))/a;
    float x0 = (a1*z0 + b1)/dnm;
    float y0 = (a2*z0 + b2)/dnm;

    // set EE position & re-calc ankles position
    SetEEParam( d_bot, Vector3(x0, y0, z0));

#ifdef DEBUG_CALC_FK_DELTA
    qDebug() << "**** Forward Kinematics ****";
    qDebug() << "Knee Position - FK";
    for ( uint8_t i = 0; i<3; i++)
    {
        qDebug() << d_bot->kneeVertex[i].x
                 << d_bot->kneeVertex[i].y
                 << d_bot->kneeVertex[i].z;
    }
    qDebug() << "EE Position result :" << x0 << y0 << z0;
#endif

    return 0;
}
/****************************************************************************
  void Draw : draw Delta model
*****************************************************************************/
void Delta::Draw() {
    uint8_t i;

#ifdef DEBUG_CALC_FK_DELTA
    float x[3], y[3], z[3];

    x[0] = 0;
    y[0] = myDelta->rEE + myDelta->kneeVertex[0].y;
    z[0] = myDelta->kneeVertex[0].z;

    x[1] = - sin120 * myDelta->rEE + myDelta->kneeVertex[1].x;
    y[1] = cos120 * myDelta->rEE + myDelta->kneeVertex[1].y;
    z[1] = myDelta->kneeVertex[1].z;

    x[2] = sin120 * myDelta->rEE + myDelta->kneeVertex[2].x;
    y[2] = cos120 * myDelta->rEE + myDelta->kneeVertex[2].y;
    z[2] = myDelta->kneeVertex[2].z;
#endif

    glBegin( GL_TRIANGLES );
    // draw base
    qglColor( Qt::lightGray);
    for ( i = 0; i<3; i++){
        glVertex3f( this->myDelta->baseVertex[i].x,
                    this->myDelta->baseVertex[i].y,
                    this->myDelta->baseVertex[i].z);
    }

    // draw hipvertex
//    qglColor( Qt::darkGray);
//    for ( i = 0; i<3; i++){
//        glVertex3f( this->myDelta->hipVertex[i].x,
//                    this->myDelta->hipVertex[i].y,
//                    this->myDelta->hipVertex[i].z);
//    }

    // draw end effector
    qglColor( Qt::blue);
    for ( i = 0; i<3; i++){
        glVertex3f( this->myDelta->ankleVertex[i].x,
                    this->myDelta->ankleVertex[i].y,
                    this->myDelta->ankleVertex[i].z);
    }
    glEnd();

    // draw 3 legs
    for ( i = 0; i<3; i++){
        glBegin( GL_LINES);
        qglColor(Qt::red);
        glVertex3f( this->myDelta->hipVertex[i].x,
                    this->myDelta->hipVertex[i].y,
                    this->myDelta->hipVertex[i].z);
        glVertex3f( this->myDelta->kneeVertex[i].x,
                    this->myDelta->kneeVertex[i].y,
                    this->myDelta->kneeVertex[i].z);

#ifdef DEBUG_CALC_FK_DELTA
        qglColor(Qt::yellow);
        glVertex3f( this->myDelta->kneeVertex[i].x,
                    this->myDelta->kneeVertex[i].y,
                    this->myDelta->kneeVertex[i].z);
        glVertex3f( x[i], y[i], z[i]);
#endif

        qglColor(Qt::cyan);
        glVertex3f( this->myDelta->kneeVertex[i].x,
                    this->myDelta->kneeVertex[i].y,
                    this->myDelta->kneeVertex[i].z);
        glVertex3f( this->myDelta->ankleVertex[i].x,
                    this->myDelta->ankleVertex[i].y,
                    this->myDelta->ankleVertex[i].z);
        glEnd();
    }

}

/****************************************************************************
  function Clone : copy new parameter into myDelta
*****************************************************************************/
void Delta::Clone(DeltaParameter newParam) {
    *(this->myDelta) = newParam;
}
/****************************************************************************
  void SetEEParam : dat lai vi tri cua End Effector va cap nhat luon gia
                       tri cua cac ankleVertex
*****************************************************************************/
void Delta::SetEEParam(DeltaParameter *data, Vector3 dstPos) {
    data->eePos = dstPos;
    data->ankleVertex[0].Set( dstPos.x, dstPos.y-data->rEE, dstPos.z);
    // ankleVertex[1] = ( eePos.x + s120 * rEE, eePos.y - c120 * rEE, eePos.z)
    data->ankleVertex[1].Set( dstPos.x + sin120 * data->rEE, dstPos.y - cos120 * data->rEE, dstPos.z);
    // ankleVertex[2] = ( eePos.x + s240 * rEE, eePos.y - c240 * rEE, eePos.z) & C120 = c240, s120 = -s240
    data->ankleVertex[2].Set( dstPos.x - sin120 * data->rEE, dstPos.y - cos120 * data->rEE, dstPos.z);
}
/****************************************************************************
  function GetThetaAngle : return gia tri theta[n]
*****************************************************************************/
float Delta::GetThetaAngle(uint8_t n) {
    if (n >= 0 && n <= 2)
        return myDelta->theta[n];
    else
        return 0;
}
/****************************************************************************
  void Rotate120 : quay vector 120 do theo chieu nguoc chieu kim dong ho
*****************************************************************************/
Vector3 Delta::Rotate120(Vector3 vector) {
    Vector3 t = vector;
    t.x = vector.x * cos120 - vector.y * sin120;
    t.y = vector.x * sin120 + vector.y * cos120;
    t.z = vector.z;
    return t;
}

/****************************************************************************
  void Rotate240 : quay vector 240 do theo chieu nguoc chieu kim dong ho
*****************************************************************************/
Vector3 Delta::Rotate240(Vector3 vector) {
    Vector3 t = vector;
    t.x = vector.x * cos120 + vector.y * sin120;
    t.y = - vector.x * sin120 + vector.y * cos120;
    t.z = vector.z;
    return t;
}
/****************************************************************************
  void r2 : thuc hien phep luy thua 2
*****************************************************************************/
float Delta::r2 (float in) {
    return in*in;
}

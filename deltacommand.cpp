#include "deltacommand.h"
#include <QDebug>

DeltaCommand::DeltaCommand(QObject *parent) :
    QThread(parent)
{
    float step = 0.5025;

    circleTraj.resize(200);
    circleTraj[0].x = -50;
    circleTraj[0].y = sqrt(50 * 50 - circleTraj[0].x * circleTraj[0].x ) - 200;

    for ( curTrajPosition = 1; curTrajPosition < circleTraj.size(); curTrajPosition++ ){
        circleTraj[curTrajPosition].x = circleTraj[curTrajPosition-1].x + step;
        circleTraj[curTrajPosition].y = sqrt(50 * 50 - circleTraj[curTrajPosition].x * circleTraj[curTrajPosition].x ) - 200;
//        qDebug() << circleTraj[curTrajPosition].x << circleTraj[curTrajPosition].y;
    }
    qDebug( "Done" );

//    id_performAnimateTimer = startTimer(20);
//    curTrajPosition = 0;
//    qDebug() << id_performAnimateTimer;
}

void DeltaCommand::linkToDeltaObj(Delta *d_bot) {
    mainDelta = d_bot;
}

uint8_t DeltaCommand::MoveToTargetPos(float x, float y, float z) {
//    float theta[3];
    return mainDelta->Set_EE_Position( Vector3(x, y, z), 0, 1);
}

// *** Goc toa do lay nhu mac dinh ***
uint8_t DeltaCommand::SetHipsAngles(float theta1, float theta2, float theta3) {
    float theta[3];
    theta[0] = theta1 * DEG2RAD;
    theta[1] = theta2 * DEG2RAD;
    theta[2] = theta3 * DEG2RAD;
    return mainDelta->Set_Hips_Angles( 0, theta, 1);
}

void DeltaCommand::StartFollowCircle(){
    id_performAnimateTimer = startTimer(20);
    curTrajPosition = 0;
}

void DeltaCommand::StopFollowCircle(){
    killTimer( id_performAnimateTimer);
}

void DeltaCommand::timerEvent(QTimerEvent *event){
//    qDebug() << event->timerId();
    if (id_performAnimateTimer == event->timerId()){
        if (curTrajPosition < circleTraj.size() )
        {
//            qDebug() << "Control data";
            MoveToTargetPos( circleTraj[curTrajPosition].x, 0, circleTraj[curTrajPosition].y);
            curTrajPosition++;
        }
        else
            curTrajPosition = 0;
    }

}

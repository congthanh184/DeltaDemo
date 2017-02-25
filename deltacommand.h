#ifndef DELTACOMMAND_H
#define DELTACOMMAND_H

#include <QThread>
#include "vector3.h"
#include "delta.h"
#include <QTimerEvent>
#include <QKeyEvent>

class DeltaCommand : public QThread
{
    Q_OBJECT

private:
    Delta *mainDelta;
    void timerEvent(QTimerEvent *);
    QVector<Vector3> circleTraj, trajBuffer;
    uint16_t curTrajPosition, trajBufferIndex;
    uint32_t id_performAnimateTimer;
public:
    explicit DeltaCommand(QObject *parent = 0);
    void linkToDeltaObj( Delta *);
    uint8_t MoveToTargetPos (float x, float y, float z);
    uint8_t SetHipsAngles( float theta1, float theta2, float theta3 );
    void StartFollowCircle();
    void StopFollowCircle();
signals:
    
public slots:

};

#endif // DELTACOMMAND_H

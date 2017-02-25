#ifndef DELTAGLWIDGET_H
#define DELTAGLWIDGET_H

#include <QGLWidget>
#include <QTime>
#include "delta.h"

class DeltaGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit DeltaGLWidget(QWidget *parent = 0);

private:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void timerEvent(QTimerEvent *event);

    Delta glDelta;
    DeltaParameter coreParam;
    int timeInterval;
    float rotz;

    QVector<Vector3> circleTraj;
signals:
    
public slots:
    void loadDeltaParam( DeltaParameter );
};

#endif // DELTAGLWIDGET_H

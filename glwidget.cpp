#include "glwidget.h"
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>

DeltaGLWidget::DeltaGLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    setWindowTitle("Delta Simulation");
    timeInterval = startTimer(15);

    float step = 0.5025;

    circleTraj.resize(200);
    circleTraj[0].x = -50;
    circleTraj[0].y = sqrt(50 * 50 - circleTraj[0].x * circleTraj[0].x ) - 200;

    for ( uint8_t curTrajPosition = 1; curTrajPosition < circleTraj.size(); curTrajPosition++ ){
        circleTraj[curTrajPosition].x = circleTraj[curTrajPosition-1].x + step;
        circleTraj[curTrajPosition].y = sqrt(50 * 50 - circleTraj[curTrajPosition].x * circleTraj[curTrajPosition].x ) - 200;
//        qDebug() << circleTraj[curTrajPosition].x << circleTraj[curTrajPosition].y;
    }
}

void DeltaGLWidget::initializeGL(){
    glShadeModel( GL_SMOOTH );
    qglClearColor( Qt::black );

    glClearDepth( 1.0f );
    glEnable( GL_DEPTH_TEST);
    glDepthFunc( GL_LEQUAL);

    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void DeltaGLWidget::resizeGL(int w, int h){
    glViewport( 0, 0, w, h);

    glMatrixMode( GL_PROJECTION);
    glLoadIdentity();

    gluPerspective( 45.0f, (GLfloat)w/h, 10.0f, 1000.0f);

    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();
}

void DeltaGLWidget::paintGL(){
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef( 0, 80, -450.0f);
//    glRotated( -30, 0, 1, 0);
    glRotated( -60, 1, 0, 0);
//    glRotated( 180, 0, 0, 1);
    glRotatef( rotz, 0.0f, 0.0f, 1.0f);
//    glRotated( 180, 0, 0, 1);
    glDelta.Draw();

    qglColor( Qt::yellow);
    glBegin(GL_LINE_STRIP);
    for (uint8_t i = 0; i < circleTraj.size(); i++){
        glVertex3f ( circleTraj[i].x, 0, circleTraj[i].y);
    }
    glEnd();

    rotz += 0.16;
}

void DeltaGLWidget::loadDeltaParam(DeltaParameter param) {
//    qDebug("glDeltaWidget got param");
    coreParam = param;
    glDelta.Clone(coreParam);    
//    qDebug() << glDelta.GetThetaAngle(0) << glDelta.GetThetaAngle(1) << glDelta.GetThetaAngle(2);
    updateGL();
}

void DeltaGLWidget::timerEvent(QTimerEvent *event) {
    if (event->timerId() == timeInterval) {
        updateGL();
    }
    QGLWidget::timerEvent(event);
}

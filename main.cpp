#include <QtGui/QApplication>
#include "mainwindow.h"

#include "delta.h"
#include "glwidget.h"
#include "deltacommand.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DeltaGLWidget deltaDisplay;    
    Delta deltaBot ( 75, 24, 0, 0, 100, 200);
    DeltaCommand *db_command = new DeltaCommand();
    MainWindow w;

    db_command->linkToDeltaObj( &deltaBot );
    w.linkDeltaControl( db_command );
    w.connect( &deltaBot, SIGNAL(UpdateDParam(DeltaParameter)), &w, SLOT(loadDeltaParam(DeltaParameter)));
//    w.connect( &w, SLOT(on_btLoadCircle_clicked()), db_command, SLOT(StartFollowCircle()));
    deltaDisplay.connect( &deltaBot, SIGNAL(UpdateDParam(DeltaParameter)), &deltaDisplay, SLOT(loadDeltaParam(DeltaParameter)));

    db_command->MoveToTargetPos( 0, 0, -250);

    deltaDisplay.resize( 600, 480);
    deltaDisplay.show();
    w.show();   

    return a.exec();
}

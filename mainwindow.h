#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "delta.h"
#include "deltacommand.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
private:
    DeltaCommand* dbCommand;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void linkDeltaControl( DeltaCommand* );
private:
    Ui::MainWindow *ui;
signals:
    void cmd_Set_Position( float, float, float);
private slots:
    void on_btSetPosition_clicked();
    void loadDeltaParam( DeltaParameter );
    void on_btSetAngles_clicked();
    void on_btLoadCircle_clicked();
};

#endif // MAINWINDOW_H

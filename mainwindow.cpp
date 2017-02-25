#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::linkDeltaControl(DeltaCommand *dbCommand){
    this->dbCommand = dbCommand;
}

void MainWindow::on_btSetPosition_clicked()
{
    dbCommand->MoveToTargetPos(ui->doubleBoxX->value(),
                               ui->doubleBoxY->value(),
                               ui->doubleBoxZ->value());
}

void MainWindow::loadDeltaParam(DeltaParameter param) {
    ui->doubleBoxTheta1->setValue(param.theta[0] * RAD2DEG);
    ui->doubleBoxTheta2->setValue(param.theta[1] * RAD2DEG);
    ui->doubleBoxTheta3->setValue(param.theta[2] * RAD2DEG);

    ui->doubleBoxX->setValue(param.eePos.x);
    ui->doubleBoxY->setValue(param.eePos.y);
    ui->doubleBoxZ->setValue(param.eePos.z);
}

void MainWindow::on_btSetAngles_clicked()
{
    dbCommand->SetHipsAngles( ui->doubleBoxTheta1->value(),
                              ui->doubleBoxTheta2->value(),
                              ui->doubleBoxTheta3->value());
}

void MainWindow::on_btLoadCircle_clicked()
{
    dbCommand->StartFollowCircle();
}

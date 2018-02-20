#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStateMachine>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tmrRed = new QTimer(this);
    tmrYellow = new QTimer(this);
    tmrGreen = new QTimer(this);

    sRed = new QState();
    sYellow = new QState();
    sGreen = new QState();

    sRed->addTransition(tmrRed, SIGNAL(timeout()), sYellow);
    sYellow->addTransition(tmrYellow, SIGNAL(timeout()), sGreen);
    sYellow->addTransition(tmrYellow, SIGNAL(timeout()), sRed);
    sGreen->addTransition(tmrGreen, SIGNAL(timeout()), sYellow);

    machine.addState(sRed);
    machine.addState(sYellow);
    machine.addState(sGreen);
    machine.setInitialState(sRed);

    sRed->assignProperty(ui->RedBut->setChecked(true), );
    sYellow->assignProperty(label, "text", "In state s2");
    sGreen->assignProperty(label, "text", "In state s3");
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_StartBut_clicked()
{
    machine.start();
}

void MainWindow::on_StopBut_clicked()
{
    machine.stop();
}

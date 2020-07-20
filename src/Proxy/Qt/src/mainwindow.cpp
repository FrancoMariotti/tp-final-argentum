#include <QtWidgets/QtWidgets>
#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(LoginMediator *loginMediator, QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    loginMediator(loginMediator){
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectButton_clicked() {
    QString host = ui->hostLineEdit->text();
    QString service = ui->serviceLineEdit->text();
    loginMediator->sendServerCredentials(host.toStdString(), service.toStdString());
}

void MainWindow::setServerStatus(bool status) {
    if(status){
        ui->serverStateLabel->setStyleSheet("QLabel{color: green;}");
        ui->serverStateLabel->setText("Server online!");
    } else {
        ui->serverStateLabel->setStyleSheet("QLabel{color: red;}");
        ui->serverStateLabel->setText("Server offline!");
    }
}


#include "moc_mainwindow.cpp"
#include "client_qt_serverlogin.h"
#include "ui_client_qt_serverlogin.h"
#include "client_qt_loginmediator.h"

QtServerLogin::QtServerLogin(LoginMediator* loginMediator, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QtServerLogin),
    loginMediator(loginMediator) {
    ui->setupUi(this);
}

QtServerLogin::~QtServerLogin() {
    delete ui;
}

void QtServerLogin::on_connectButton_clicked() {
    QString host = ui->hostLineEdit->text();
    QString service = ui->serviceLineEdit->text();

    loginMediator->sendServerCredentials(host.toStdString(), service.toStdString());
}

void QtServerLogin::setServerStatus(bool status) {
    if(status){
        ui->serverStateLabel->setStyleSheet("QLabel{color: green;}");
        ui->serverStateLabel->setText("Server online!");
    } else {
        ui->serverStateLabel->setStyleSheet("QLabel{color: red;}");
        ui->serverStateLabel->setText("Server offline!");
    }
}

#include "moc_client_qt_serverlogin.cpp"

#include <QString>
#include <QTextStream>
#include <QMessageBox>
#include "client_qt_characterlogin.h"
#include "ui_client_qt_characterlogin.h"
#include "client_qt_loginmediator.h"


QtCharacterLogin::QtCharacterLogin(LoginMediator* loginMediator, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QtCharacterLogin),
    loginMediator(loginMediator) {
    ui->setupUi(this);
}

QtCharacterLogin::~QtCharacterLogin() {
    delete ui;
}

void QtCharacterLogin::on_loginPushButton_clicked() {
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QMessageBox::information(this, "Login", "Comprobando credenciales");
    loginMediator->sendCharacterLogin(username.toStdString(), password.toStdString());
}


void QtCharacterLogin::setLoginLabel(bool login){
    if(login){
        ui->loginLabel->setStyleSheet("QLabel{color:green;}");
        ui->loginLabel->setText("Login exitoso");
    } else {
        ui->loginLabel->setStyleSheet("QLabel{color:red;}");
        ui->loginLabel->setText("Usuario o contraseña incorrectos");
    }
}

void QtCharacterLogin::showMessageBox(const std::string& text){
    QMessageBox::information(this, "Login", QString(text.c_str()));
}

void QtCharacterLogin::on_signUpPushButton_clicked(){
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QMessageBox::information(this, "Login", "Comprobando credenciales");
    loginMediator->sendLoginAndGoToCreationWindow(username.toStdString(), password.toStdString());
}

#include "moc_client_qt_characterlogin.cpp"
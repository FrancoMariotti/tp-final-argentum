#include <QtWidgets/QMessageBox>
#include "QCloseEvent"
#include "loginform.h"
#include "ui_loginform.h"

LoginForm::LoginForm(LoginMediator *loginMediator, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm),
    loginMediator(loginMediator)
{
    ui->setupUi(this);
    this->setFixedWidth(800);
    this->setFixedHeight(700);
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_loginPushButton_clicked() {
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QMessageBox::information(this, "Login", "Comprobando credenciales");
    loginMediator->sendCharacterLogin(username.toStdString(), password.toStdString());
}

void LoginForm::setLoginLabel(bool login){
    if(login){
        ui->loginLabel->setStyleSheet("QLabel{color:green;}");
        ui->loginLabel->setText("Login exitoso");
    } else {
        ui->loginLabel->setStyleSheet("QLabel{color:red;}");
        ui->loginLabel->setText("Usuario o contraseña incorrectos");
    }
}

void LoginForm::showMessageBox(const std::string& text){
    QMessageBox::information(this, "Login", QString(text.c_str()));
}

void LoginForm::on_signUpPushButton_clicked(){
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QMessageBox::information(this, "Login", "Comprobando credenciales");
    loginMediator->sendLoginAndGoToCreationWindow(username.toStdString(), password.toStdString());
}



void LoginForm::closeEvent(QCloseEvent *event) {
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "argentum",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Cancel | QMessageBox::Yes,
                                                                QMessageBox::Yes);

    if (resBtn == QMessageBox::Yes) {
        QWidget::closeEvent(event);
    } else {
        event->ignore();
    }
}

#include "moc_loginform.cpp"
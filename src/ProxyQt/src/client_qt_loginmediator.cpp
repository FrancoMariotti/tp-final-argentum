#include "client_qt_loginmediator.h"
#include "client_qt_serverlogin.h"
#include "client_qt_characterlogin.h"
#include "client_qt_charactercreation.h"
#include <Proxy/src/common_message.h>
#include "../../Proxy/src/common_proxy_socket.h"

LoginMediator::LoginMediator(ProxySocket& proxySocket) :
    proxySocket(proxySocket){
    qtServerLogin = new QtServerLogin(this);
    qtCharacterLogin = new QtCharacterLogin(this);
    qtCharacterCreation = new QtCharacterCreation(this);
}


void LoginMediator::sendServerCredentials(const std::string& host,const std::string& service){
    if(!host.empty() && !service.empty()){
        proxySocket.writeToServer(std::unique_ptr<Message>(new Login(host, service, PROXY_CONNECT_MESSAGE_ID)));
        std::unique_ptr<Message> msg = proxySocket.readClient();
        if(msg->getId() == ACCEPT_CREDENTIALS_MESSAGE_ID && msg->getAnswer()){
            qtServerLogin->setServerStatus(true);
            qtServerLogin->hide();
            qtCharacterLogin->show();
        } else {
            qtServerLogin->setServerStatus(false);
        }
    }
}

void LoginMediator::sendCharacterLogin(const std::string& username, const std::string& password){
    if(!username.empty() && !password.empty()){
        proxySocket.writeToServer(std::unique_ptr<Message>
                                          (new Login(username,
                                                     password, LOGIN_MESSAGE_ID)));
        std::unique_ptr<Message> msg = proxySocket.readClient();
        if(msg->getId() == ACCEPT_CREDENTIALS_MESSAGE_ID){
            qtCharacterLogin->setLoginLabel(msg->getAnswer());
        }
    } else {
        qtCharacterLogin->showMessageBox("Debe completar los campos de usuario y contraseña");
    }


}

void LoginMediator::sendLoginAndGoToCreationWindow(const std::string& username, const std::string& password){
    if(!username.empty() && !password.empty()){
        proxySocket.writeToServer(std::unique_ptr<Message>
                                          (new Login(username,
                                                     password, SIGNUP_MESSAGE_ID)));
        std::unique_ptr<Message> msg = proxySocket.readClient();
        if(msg->getId() == ACCEPT_CREDENTIALS_MESSAGE_ID && msg->getAnswer()){
            this->confirmed_username = username;
            this->confirmed_password = password;
            qtCharacterLogin->setLoginLabel(msg->getAnswer());
            qtCharacterLogin->hide();
            qtCharacterCreation->show();
        }
    } else {
        qtCharacterLogin->showMessageBox("Debe completar los campos de usuario y contraseña");
    }
}

void LoginMediator::sendCharacterCreation(const std::string& s_race, const std::string& s_class){
    std::string text = "Usuario: " + confirmed_username + "\nContraseña: " + confirmed_password
                       + "\nRaza: " + s_race + "\nClase: " + s_class;
    qtCharacterLogin->showMessageBox(text);
    proxySocket.writeToServer(std::unique_ptr<Message>
            (new Create(confirmed_username,
                    confirmed_password, s_race, s_class)));
    std::unique_ptr<Message> msg = proxySocket.readClient();
    std::cout << msg->getAnswer() << std::endl;
    if(msg->getId() == ACCEPT_CREDENTIALS_MESSAGE_ID && msg->getAnswer()){
        qtCharacterLogin->showMessageBox("Credenciales aceptadas, ingresando al mundo");
    } else {
        qtCharacterLogin->setLoginLabel(false);
    }
}

void LoginMediator::changeToLoginScreen(){
    qtCharacterCreation->hide();
    qtCharacterLogin->show();
}

void LoginMediator::show(){
    qtServerLogin->show();
}

LoginMediator::~LoginMediator(){
    delete qtServerLogin;
    delete qtCharacterLogin;
    delete qtCharacterCreation;
}

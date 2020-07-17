#include "client_qt_loginmediator.h"
#include "client_qt_serverlogin.h"
#include "client_qt_characterlogin.h"
#include "client_qt_charactercreation.h"
#include <Proxy/src/common_message.h>
#include <Proxy/src/common_socket.h>
#include "../../Proxy/src/common_proxy_socket.h"

#define LOGIN_COMMAND 'l'
#define SIGNUP_COMMAND 's'
#define CREATE_COMMAND 'c'
#define USER_EXISTS 1

LoginMediator::LoginMediator(Socket& clientSocket) :
    clientSocket(clientSocket){
    qtServerLogin = new QtServerLogin(this);
    qtCharacterLogin = new QtCharacterLogin(this);
    qtCharacterCreation = new QtCharacterCreation(this);
}


void LoginMediator::sendServerCredentials(const std::string& host,const std::string& service){
    if(!host.empty() && !service.empty()){
        //proxySocket.writeToServer(std::unique_ptr<Message>(new Login(host, service, PROXY_CONNECT_MESSAGE_ID)));
        //std::unique_ptr<Message> msg = proxySocket.readClient();
        //if(msg->getId() == ACCEPT_CREDENTIALS_MESSAGE_ID && msg->getAnswer()){
        if(clientSocket.connect(host.c_str(), service.c_str()) == 0){
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
        /*proxySocket.writeToServer(std::unique_ptr<Message>
                                          (new Login(username,
                                                     password, LOGIN_MESSAGE_ID)));
        std::unique_ptr<Message> msg = proxySocket.readClient();*/
        /*if(msg->getId() == ACCEPT_CREDENTIALS_MESSAGE_ID){
            qtCharacterLogin->setLoginLabel(msg->getAnswer());
        }*/
        char msg = LOGIN_COMMAND;
        char answer;
        clientSocket.send(&msg, sizeof(char));
        clientSocket.recieve(&answer, sizeof(char));
        qtCharacterLogin->setLoginLabel(answer == USER_EXISTS);
        /*Aca cierro la app de login*/
        //loginMediator->close()
    } else {
        qtCharacterLogin->showMessageBox("Debe completar los campos de usuario y contraseña");
    }
}

void LoginMediator::sendLoginAndGoToCreationWindow(const std::string& username, const std::string& password){
    if(!username.empty() && !password.empty()){
        /*proxySocket.writeToServer(std::unique_ptr<Message>
                                          (new Login(username,
                                                     password, SIGNUP_MESSAGE_ID)));
        std::unique_ptr<Message> msg = proxySocket.readClient();
        if(msg->getId() == ACCEPT_CREDENTIALS_MESSAGE_ID && msg->getAnswer()){
            qtCharacterLogin->setLoginLabel(msg->getAnswer());
            qtCharacterLogin->hide();
            qtCharacterCreation->show();
        }*/
        char msg = SIGNUP_COMMAND;
        char answer;
        clientSocket.send(&msg, sizeof(char));
        clientSocket.recieve(&answer, sizeof(char));
        if(answer != USER_EXISTS){
            this->confirmed_username = username;
            this->confirmed_password = password;
            qtCharacterLogin->setLoginLabel(answer == 0);
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
    /*proxySocket.writeToServer(std::unique_ptr<Message>
            (new Create(confirmed_username,
                    confirmed_password, s_race, s_class)));
    std::unique_ptr<Message> msg = proxySocket.readClient();
    std::cout << msg->getAnswer() << std::endl;*/
    char msg = CREATE_COMMAND;
    char answer;
    clientSocket.send(&msg, sizeof(char));
    clientSocket.recieve(&answer, sizeof(char));
    //if(/*msg->getId() == ACCEPT_CREDENTIALS_MESSAGE_ID && msg->getAnswer()*/)
    if(answer == 1){
        qtCharacterLogin->showMessageBox("Credenciales aceptadas, ingresando al mundo");
        /*Aca cierro la app de login*/
        //loginMediator->close()
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

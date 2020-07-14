#include <Proxy/src/common_message.h>
#include "client_qt_loginmediator.h"
#include "client_qt_serverlogin.h"
#include "client_qt_characterlogin.h"

#include "../../Proxy/src/common_proxy_socket.h"
LoginMediator::LoginMediator(ProxySocket& proxySocket) :
    proxySocket(proxySocket) {
    qtServerLogin = new QtServerLogin(this);
    qtCharacterLogin = new QtCharacterLogin(this);
}


void LoginMediator::changeWindowToCharacterLogin(){

}

void LoginMediator::sendServerCredentials(const std::string& host,const std::string& service){
    //envio credenciales y si son correctas cambio el window
    //debe ser bloqueante,no puedo seguir hasta recibir respuesta no lo envio a ningun thread
    //protocol.send()
    //if(se conecto al server)
    //protocl.recv()
    if(!host.empty() && !service.empty()){
        /*En realidad aca no hay ningun canal levantado ya que se intenta hacer un socket.connect
         **/
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

void LoginMediator::sendCharacterCreation(const std::string& username, const std::string& password,
                                          const std::string& s_race, const std::string& s_class){

    if(!username.empty() && !password.empty()){
        std::string text = "Usuario: " + username + "\nContraseña: " + password
                + "\nRaza: " + s_race + "\nClase: " + s_class;
        qtCharacterLogin->showMessageBox(text);
        proxySocket.writeToServer(std::unique_ptr<Message>(new Create(username, password, s_race, s_class)));
        std::unique_ptr<Message> msg = proxySocket.readClient();
        std::cout << msg->getAnswer() << std::endl;
        if(msg->getId() == ACCEPT_CREDENTIALS_MESSAGE_ID && msg->getAnswer()){
            qtCharacterLogin->showMessageBox("Credenciales aceptadas, ingresando al mundo");
        } else {
            qtCharacterLogin->setLoginLabel(false);
        }
    } else {
        qtCharacterLogin->showMessageBox("Debe completar los campos de usuario y contraseña");
    }
}

void LoginMediator::show(){
    qtServerLogin->show();
}

LoginMediator::~LoginMediator(){
    delete qtServerLogin;
    delete qtCharacterLogin;
}

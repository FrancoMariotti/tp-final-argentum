#include "client_qt_loginmediator.h"
#include "client_qt_charactercreation.h"
#include "mainwindow.h"
#include "loginform.h"
#include "charactercreationform.h"
#include <Common/Messages/Message.h>
#include <Common/Socket.h>
#include <QtGui/QPainter>
#include <QtWidgets/QtWidgets>

#define USER_EXISTS 1

LoginMediator::LoginMediator(Socket &clientSocket, std::string &gui_username,bool& finished) :
    clientSocket(clientSocket),
    gui_username(gui_username),
    finished(finished){
    mainwindow = new MainWindow(this);
    loginForm = new LoginForm(this);
    creationForm = new CharacterCreationForm(this);
}

/*Realiza un connect con el socket, caso invalida se le informa al cliente para que vuelva a intentar
 * caso en que se conecta se pasa a la pantalla de login*/
void LoginMediator::sendServerCredentials(const std::string& host,const std::string& service){
    if(!host.empty() && !service.empty()){
         if(clientSocket.connect(host.c_str(), service.c_str()) == 0){
             mainwindow->setServerStatus(true);
             mainwindow->hide();
             loginForm->show();
        } else {
             mainwindow->setServerStatus(false);
        }
    }
}

/*Este evento es en el caso de Iniciar Sesion, el server verifica si el usuario y la contraseña son correctos
 * caso que sea cierto server devuelve un 1 y cierro la App, caso contrario se indica al cliente que el input fue erroneo*/
void LoginMediator::sendCharacterLogin(const std::string& username, const std::string& password){
    if(!username.empty() && !password.empty()) {
        int answer;
        Login loginMsg(username,password,LOGIN_MESSAGE_ID);
        protocol.send(clientSocket, &loginMsg);
        answer = protocol.recieve(clientSocket,0);
        std::cout << "Iniciar Sesion: " << answer << std::endl;
        if (answer == USER_EXISTS) {
            loginForm->setLoginLabel(true);
            gui_username = username;
            /*Aca cierro la app de login*/
            finished = true;
            this->close();
        } else {
            loginForm->setLoginLabel(false);
        }
    } else {
        loginForm->showMessageBox("Debe completar los campos de usuario y contraseña");
    }
}

/*Caso cliente elija SignUp, se envia al server usuario y contraseña para verificar si estos existen
 * En caso de que NO existan, se cambia a la ventana de creacion. Caso contrario se informa de que
 * el usuario existe*/
void LoginMediator::sendLoginAndGoToCreationWindow(const std::string& username, const std::string& password){
    if(!username.empty() && !password.empty()){
        int answer;
        Login loginMsg(username,password,SIGNUP_MESSAGE_ID);
        protocol.send(clientSocket,&loginMsg);
        answer = protocol.recieve(clientSocket,0);
        std::cout << "Registrarse: " << answer << std::endl;
        if(answer == 1){
            this->confirmed_username = username;
            this->confirmed_password = password;
            loginForm->setLoginLabel(true);
            loginForm->hide();
            //qtCharacterCreation->show();
            creationForm->show();
        } else {
            loginForm->showMessageBox("El usuario ya existe");
            loginForm->setLoginLabel(false);
        }
    } else {
        loginForm->showMessageBox("Debe completar los campos de usuario y contraseña");
    }
}

/*Pre: usuario y contraseña deben encontrarse sin uso en el server
 * Post: envia al server el usuario, password raza y clase del NUEVO jugador y sale de la App*/
void LoginMediator::sendCharacterCreation(const std::string& s_race, const std::string& s_class){
    std::string text = "Usuario: " + confirmed_username + "\nContraseña: " + confirmed_password
                       + "\nRaza: " + s_race + "\nClase: " + s_class;
    loginForm->showMessageBox(text);
    Create create(confirmed_username,confirmed_password,s_race,s_class);
    protocol.send(clientSocket,&create);
    gui_username = confirmed_username;
    finished = true;
    this->close();
}

void LoginMediator::changeToLoginScreen() {
    creationForm->hide();
    loginForm->reset();
    loginForm->show();
}

void LoginMediator::show() {
    mainwindow->show();
}

void LoginMediator::close() {
    mainwindow->close();
    loginForm->close();
    creationForm->close();
}

LoginMediator::~LoginMediator(){
    delete mainwindow;
    delete loginForm;
    delete creationForm;
}

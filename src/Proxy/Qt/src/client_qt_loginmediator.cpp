#include "client_qt_loginmediator.h"
#include "client_qt_serverlogin.h"
#include "client_qt_characterlogin.h"
#include "client_qt_charactercreation.h"
#include <Common/Message.h>
#include <Common/Socket.h>
#include <QtGui/QPainter>

#define LOGIN_COMMAND 'l'
#define SIGNUP_COMMAND 's'
#define CREATE_COMMAND 'c'
#define USER_EXISTS 1

LoginMediator::LoginMediator(Socket &clientSocket, std::string &gui_username,bool& finished) :
    clientSocket(clientSocket),
    gui_username(gui_username),
    finished(finished){
    qtServerLogin = new QtServerLogin(this);
    qtServerLogin->setGeometry(0, 0, 1000, 900);
    QPixmap bkgnd("./../assets/background.jpg");
    bkgnd = bkgnd.scaled(qtServerLogin->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    qtServerLogin->setPalette(palette);
    qtCharacterLogin = new QtCharacterLogin(this);
    qtCharacterCreation = new QtCharacterCreation(this);
}

/*Realiza un connect con el socket, caso invalida se le informa al cliente para que vuelva a intentar
 * caso en que se conecta se pasa a la pantalla de login*/
void LoginMediator::sendServerCredentials(const std::string& host,const std::string& service){
    if(!host.empty() && !service.empty()){
         if(clientSocket.connect(host.c_str(), service.c_str()) == 0){
             qtServerLogin->setServerStatus(true);
             qtServerLogin->hide();
             qtCharacterLogin->show();
        } else {
             qtServerLogin->setServerStatus(false);
        }
    }
}

/*Este evento es en el caso de Iniciar Sesion, el server verifica si el usuario y la contraseña son correctos
 * caso que sea cierto server devuelve un 1 y cierro la App, caso contrario se indica al cliente que el input fue erroneo*/
void LoginMediator::sendCharacterLogin(const std::string& username, const std::string& password){
    if(!username.empty() && !password.empty()) {
        int answer;
        Message *msg = new Login(username, password, LOGIN_MESSAGE_ID);
        protocol.send(clientSocket, msg);
        delete msg;
        answer = protocol.recieve(clientSocket,0);
        //clientSocket.receive((char*)&answer, sizeof(int));
        std::cout << "Iniciar Sesion: " << answer << std::endl;
        if (answer == USER_EXISTS) {
            qtCharacterLogin->setLoginLabel(true);
            Connect connect(username, "", "");
            protocol.send(clientSocket, &connect);
            gui_username = username;
            /*Aca cierro la app de login*/
            finished = true;
            this->close();
        } else {
            qtCharacterLogin->setLoginLabel(false);
        }
    } else {
        qtCharacterLogin->showMessageBox("Debe completar los campos de usuario y contraseña");
    }
}

/*Caso cliente elija SignUp, se envia al server usuario y contraseña para verificar si estos existen
 * En caso de que NO existan, se cambia a la ventana de creacion. Caso contrario se informa de que
 * el usuario existe*/
void LoginMediator::sendLoginAndGoToCreationWindow(const std::string& username, const std::string& password){
    if(!username.empty() && !password.empty()){
        int answer;
        Message* msg = new Login(username, password, LOGIN_MESSAGE_ID);
        protocol.send(clientSocket,msg);
        delete msg;
        answer = protocol.recieve(clientSocket,0);
        //clientSocket.receive((char*)&answer, sizeof(int));
        std::cout << "Registrarse: " << answer << std::endl;
        if(answer == 0){
            this->confirmed_username = username;
            this->confirmed_password = password;
            qtCharacterLogin->setLoginLabel(true);
            qtCharacterLogin->hide();
            qtCharacterCreation->show();
        } else {
            qtCharacterLogin->showMessageBox("El usuario ya existe");
            qtCharacterLogin->setLoginLabel(false);
        }
    } else {
        qtCharacterLogin->showMessageBox("Debe completar los campos de usuario y contraseña");
    }
}

/*Pre: usuario y contraseña deben encontrarse sin uso en el server
 * Post: envia al server el usuario, password raza y clase del NUEVO jugador y sale de la App*/
void LoginMediator::sendCharacterCreation(const std::string& s_race, const std::string& s_class){
    std::string text = "Usuario: " + confirmed_username + "\nContraseña: " + confirmed_password
                       + "\nRaza: " + s_race + "\nClase: " + s_class;
    qtCharacterLogin->showMessageBox(text);
    //char answer;
    Message* msg = new Connect(confirmed_username, s_race, s_class);
    protocol.send(clientSocket,msg);
    delete msg;
    gui_username = confirmed_username;
    finished = true;
    this->close();

    /**/
    //clientSocket.receive(&answer, sizeof(char));
    /*
    if(answer == 1){
        qtCharacterLogin->showMessageBox("Credenciales aceptadas, ingresando al mundo");
        //qtCharacterLogin->close();
    } else {
        qtCharacterLogin->setLoginLabel(false);
    }*/
}

void LoginMediator::changeToLoginScreen(){
    qtCharacterCreation->hide();
    qtCharacterLogin->show();
}

void LoginMediator::show(){
    qtServerLogin->show();
}

void LoginMediator::close(){
    qtServerLogin->close();
    qtCharacterLogin->close();
    qtCharacterCreation->close();
}

LoginMediator::~LoginMediator(){
    delete qtServerLogin;
    delete qtCharacterLogin;
    delete qtCharacterCreation;
}

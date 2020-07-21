#ifndef LOGINMEDIATOR_H
#define LOGINMEDIATOR_H

#include <string>
#include <Common/Protocol.h>

class Socket;
class MainWindow;
class LoginForm;
class CharacterCreationForm;
class QtCharacterCreation;
class QtCharacterLogin;
class QtServerLogin;
class LoginMediator {

private:
    MainWindow* mainwindow;
    LoginForm* loginForm;
    CharacterCreationForm* creationForm;
    QtCharacterCreation* qtCharacterCreation;

    Protocol protocol;
    Socket& clientSocket;
    std::string& gui_username;
    std::string confirmed_username;
    std::string confirmed_password;
    bool& finished;

public:
    explicit LoginMediator(Socket &clientSocket, std::string &gui_username,bool& finished);
    ~LoginMediator();
    void sendServerCredentials(const std::string& host,const std::string& service);
    void sendCharacterLogin(const std::string& username, const std::string& password);
    void sendLoginAndGoToCreationWindow(const std::string& username, const std::string& password);
    void sendCharacterCreation(const std::string& s_race, const std::string& s_class);
    void changeToLoginScreen();
    void show();
    void close();
};

#endif // LOGINMEDIATOR_H

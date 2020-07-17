#ifndef LOGINMEDIATOR_H
#define LOGINMEDIATOR_H

#include <string>

class Socket;
class QtCharacterCreation;
class QtCharacterLogin;
class QtServerLogin;
class LoginMediator {
private:
    QtServerLogin* qtServerLogin;
    QtCharacterLogin* qtCharacterLogin;
    QtCharacterCreation* qtCharacterCreation;

    Socket& clientSocket;
    std::string confirmed_username;
    std::string confirmed_password;

public:
    explicit LoginMediator(Socket& clientSocket);

    ~LoginMediator();

    void sendServerCredentials(const std::string& host,const std::string& service);

    void sendCharacterLogin(const std::string& username, const std::string& password);

    void sendLoginAndGoToCreationWindow(const std::string& username, const std::string& password);

    void sendCharacterCreation(const std::string& s_race, const std::string& s_class);

    void changeToLoginScreen();

    void show();
};

#endif // LOGINMEDIATOR_H

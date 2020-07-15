#ifndef LOGINMEDIATOR_H
#define LOGINMEDIATOR_H

#include <string>

class ProxySocket;
class QtCharacterCreation;
class QtCharacterLogin;
class QtServerLogin;
class LoginMediator {
private:
    QtServerLogin* qtServerLogin;
    QtCharacterLogin* qtCharacterLogin;
    QtCharacterCreation* qtCharacterCreation;

    enum state{
        SERVER_LOGIN,
        CHARACTER_LOGIN
    };

    ProxySocket& proxySocket;
    std::string confirmed_username;
    std::string confirmed_password;

public:
    explicit LoginMediator(ProxySocket& proxySocket);

    ~LoginMediator();

    void sendServerCredentials(const std::string& host,const std::string& service);

    void sendCharacterLogin(const std::string& username, const std::string& password);

    void sendLoginAndGoToCreationWindow(const std::string& username, const std::string& password);

    void sendCharacterCreation(const std::string& s_race, const std::string& s_class);

    void changeToLoginScreen();

    void show();
};

#endif // LOGINMEDIATOR_H

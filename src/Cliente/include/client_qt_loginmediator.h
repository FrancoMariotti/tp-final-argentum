#ifndef LOGINMEDIATOR_H
#define LOGINMEDIATOR_H

#include <string>

class ProxySocket;
class QtCharacterLogin;
class QtServerLogin;
class LoginMediator {
private:
    ProxySocket& proxySocket;
    QtServerLogin* qtServerLogin;
    QtCharacterLogin* qtCharacterLogin;

    enum state{
        SERVER_LOGIN,
        CHARACTER_LOGIN
    };

public:
    explicit LoginMediator(ProxySocket& proxySocket);

    ~LoginMediator();

    void changeWindowToCharacterLogin();

    void sendServerCredentials(const std::string& host,const std::string& service);

    void sendCharacterLogin(const std::string& username, const std::string& password);

    void sendCharacterCreation(const std::string& username, const std::string& password,
                               const std::string& s_race, const std::string& s_class);

    void show();
};

#endif // LOGINMEDIATOR_H

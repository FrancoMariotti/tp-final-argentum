#ifndef ARGENTUM_SERVER_H
#define ARGENTUM_SERVER_H


#include <Server/Model/Game.h>
#include "ThAcceptor.h"

class Server {
    bool keepTalking;
    Game game;
    ThAcceptor clientAcceptor;
    std::map<std::string,int> connectionsTable;
    ProtectedConnections clients;
    ProtectedList<std::unique_ptr<Message>> events;

    void sendInitialMessages(MessageSerializer &serializer, std::string &username, int connectionId);
    void handleEvent(MessageSerializer &serializer, std::unique_ptr<Message>& msg);
public:
    void readInput();
    explicit Server(const std::string& service,const std::string& configFile,
            const std::string& playersInfoMapFile, const std::string& playersInfoFile);

    void start();
};


#endif //ARGENTUM_SERVER_H

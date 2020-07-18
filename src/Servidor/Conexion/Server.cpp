#include "ProtectedConnections.h"
#include "Server.h"
#include <thread>
#define END_SIGNAL 'c'

Server::Server(const std::string& service,const std::string& configFile,
        const std::string& playersInfoMapFile, const std::string& playersInfoFile):
                    game(configFile, playersInfoMapFile, playersInfoFile),
                    clientAcceptor(service,clients,events) {
    keepTalking = true;
    game.initialize();
}

void Server::readInput() {
    char input = 0;
    while (input != END_SIGNAL){
        std::cin >> input;
    }
    keepTalking = false;
}

void Server::start() {
    std::cout << "Server is running" << std::endl;

    std::thread first(&Server::readInput,this);
    MessageSerializer serializer;
    this->clientAcceptor.start();
    //falta agregar un try/catch en caso de que salte alguna excepcion finalizar el server.
    while(keepTalking) {
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();
        std::list<std::unique_ptr<Message>> messages = events.consume();
        for (auto & msg : messages) {
            std::cout << "MESSAGE ID:" << msg->getId() <<std::endl;
            if (msg->getId() == LOGIN_MESSAGE_ID) {
                t_client_login data = msg->getLoginData();
                bool result = game.isUsernameRegistered(data.username);
                char answer = result ? 1:0;
                clients.sendMessage(msg->getConnectionlId(),-1,std::to_string(answer));
            }
            if (msg->getId() == CONNECT_MESSAGE_ID) {
                t_create_connect data = msg->getConnectData();
                game.createPlayer(data.username,data.race,data.charClass);
                connectionsTable[data.username] = msg->getConnectionlId();
                std::queue<Message*> initialMessages = game.initializeWorld();
                while(!initialMessages.empty()) {
                    Message* update = initialMessages.front();
                    std::string updateData = serializer.serialize(update);
                    if(update->getId() == SPAWN_PC_MESSAGE_ID) {
                        clients.broadcast(SPAWN_PC_MESSAGE_ID,updateData);
                    } else {
                        clients.sendMessage(msg->getConnectionlId(),update->getId(),updateData);
                    }
                    initialMessages.pop();
                    delete update;
                }
            }
            if (msg->getId() == MOVEMENT_MESSAGE_ID) {
                location_t location = msg->getLocation();
                Offset offset(location.x, location.y);
                game.movePlayer(location.id,offset);
            }
            if (msg->getId() == COMMAND_MESSAGE_ID) {
                game.executeCommand(msg);
            }
            if (msg->getId() == USE_ITEM_MESSAGE_ID) {
                int connectionId = msg->getConnectionlId();
                auto result = std::find_if(
                        connectionsTable.begin(),
                        connectionsTable.end(),
                        [connectionId](std::pair<std::string,int> connection)
                                    {return connection.second == connectionId; });
                game.equip(result->first, msg->getIndex());
            }
            if (msg->getId() == PLAYER_ATTACK_MESSAGE_ID) {
                location_t attackInfo = msg->getLocation();
                Position pos(attackInfo.x, attackInfo.y);
                game.attack(attackInfo.id, pos);
            }
        }
        float looptimeInSeconds = 60 * 0.001;
        game.updateModel(looptimeInSeconds);
        game.persistPlayersData(looptimeInSeconds);
        end = std::chrono::system_clock::now();
        int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
                (end-start).count();
        std::this_thread::sleep_for(std::chrono::milliseconds(60- elapsed_seconds));

        while (game.directedUpdateAvailable()) {
            std::tuple<std::string,Message*> update = game.nextDirectedUpdate();
            std::string destinatary = std::get<0>(update);
            Message* message = std::get<1>(update);
            std::string dataUpdate = serializer.serialize(message);
            clients.sendMessage(connectionsTable.at(destinatary),message->getId(),dataUpdate);
            delete message;
        }

        while (game.broadcastUpdateAvailable()) {
            Message* update = game.nextBroadCastUpdate();
            std::string dataUpdate = serializer.serialize(update);
            clients.broadcast(update->getId(),dataUpdate);
            delete update;
        }

    }
    first.join();
    clientAcceptor.stop();
    clientAcceptor.join();

    std::cout << "Server finaliza run" << std::endl;
}


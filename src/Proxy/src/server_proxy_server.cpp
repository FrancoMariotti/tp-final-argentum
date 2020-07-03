#include "server_proxy_server.h"
#include "common_proxy_socket.h"
#include "common_message.h"
#include "../../Servidor/Modelo/Game.h"
#include "../../Servidor/Modelo/Event.h"
#include "../../Servidor/Modelo/EventMove.h"
#include "../../Servidor/Modelo/NormalWeapon.h"

ProxyServer::ProxyServer(ProxySocket& proxySocket) :
    keepListening(true),
    proxySocket(proxySocket)
    {}

void ProxyServer::run() {
    std::cout << "Server is running" << std::endl;
    Game game("config/config.json");
    game.createPlayer("franco", "human", "wizard");
    //Initialize Player debe mandar vida,mana,nivel,experiencia,raza, clase,armaduras, armas
    game.initializeMap(proxySocket);
    game.initialize();
    auto* sword = new NormalWeapon("sword", 2, 5, 0);
    game.storeInInventory("franco",sword);
    auto* axe = new NormalWeapon("axe", 3, 6, 0);
    game.storeInInventory("franco",axe);
    auto* shield = new Protection("turtleShell", 4, 6, SHIELD, 0);
    game.storeInInventory("franco", shield);
    auto* shield2 = new Protection("ironShield", 5, 7, SHIELD, 0);
    game.storeInInventory("franco", shield2);
    game.equip("franco", 0);
    game.equip("franco", 1);
    game.sendUpdates(proxySocket);
    try{

        while(this->keepListening) {
            /*Si no hay eventos se bloquea*/
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();
            std::unique_ptr<Message> msg;
            if(!proxySocket.isEmpty()) {
                msg = proxySocket.readServer();

                std::cout << "MESSAGE ID:" << msg->getId() <<std::endl;
                if (msg->getId() == MOVEMENT_MESSAGE_ID) {
                    Offset offset(msg->getPlayerVelX(), msg->getPlayerVelY());
                    Event* move = new EventMove(offset);
                    move->execute(game, "franco");
                    delete move;
                }
                if (msg->getId() == COMMAND_MESSAGE_ID) {
                   game.executeCommand(msg);
                }
                if (msg->getId() == USE_ITEM_MESSAGE_ID) {
                    game.equip("franco", msg->getIndex());
                }
                if (msg->getId() == PLAYER_ATTACK_MESSAGE_ID) {
                    t_player_attack attackInfo = msg->getAttack();
                    Position pos(attackInfo.enemy_x, attackInfo.enemy_y);
                    game.attack(attackInfo.username, pos);
                }
            }
            float looptimeInSeconds = 60 * 0.001;
            game.updateModel(looptimeInSeconds);
            end = std::chrono::system_clock::now();
            int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
                    (end-start).count();
            std::this_thread::sleep_for(std::chrono::milliseconds(60- elapsed_seconds));
            game.sendUpdates(proxySocket);
        }
    } catch (ClosedQueueException &e){

    }

    std::cout << "Server finaliza run" << std::endl;
}

void ProxyServer::start() {
    Thread::start();
}

void ProxyServer::stop() {
    this->keepListening = false;
}

ProxyServer::~ProxyServer() {}

bool ProxyServer::somethingToRead() {
    return proxySocket.isEmpty();
}

#include "Game.h"
#include "Factory.h"

Game::Game(std::string mapFile) {
    MapFactory factory(mapFile);
    map = factory.create();
}

void Game::createPlayer(std::string name) {
    //if (players.find(name) != players.end()) {
    if(players.count(name) > 0) {
        //Ya existe un jugador con ese nombre por lo tanto no lo puedo agregar
        return;
    }
    //LO HAGO BASICO PARA QUE FUNCIONE ASI NOMAS
    Player player(map);
    players.insert(std::pair<std::string, Player>(name, std::move(player)));
}

void Game::movePlayer(std::string playerName, Offset offset) {
    //(players[playerName]).move(offset);
    players.at(playerName).move(offset);
}

Game::~Game() = default; /*{
    std::vector<Player*>::iterator it;
    for (it = players.begin(); it != players.end(); it++) {
        delete (*it);
    }
}*/
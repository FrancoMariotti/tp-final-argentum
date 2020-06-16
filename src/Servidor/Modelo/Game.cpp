//
// Created by franco on 15/6/20.
//

#include "Game.h"
#include "Factory.h"

Game::Game(std::string mapFile) {
    MapFactory factory(mapFile);
    map = factory.create();
}

Game::~Game() {
    /*std::vector<Player*>::iterator it;
    for (it = players.begin(); it != players.end(); it++) {
        delete (*it);
    }*/
}

void Game::createPlayer(std::string name) {
    if (players.find(name) != players.end()) {
        //Ya existe un jugador con ese nombre por lo tanto no lo puedo agregar
        return;
    }
    //LO HAGO BASICO PARA QUE FUNCIONE ASI NOMAS
    players.insert(std::pair<std::string, Player>(name, Player(map)));
}

bool Game::movePlayer(std::string playerName, Offset offset) {
    (players[playerName]).move(offset);
}
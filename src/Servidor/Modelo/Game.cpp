#include "Game.h"
#include "Factory.h"
#include "PlayableCharacter.h"
#include "Update.h"

Game::Game(std::string configFile): factoryCharacters(configFile,map) {
    MapFactory factory(configFile);
    map = factory.create();
}

void Game::createPlayer(const std::string& name) {
    if(players.count(name) > 0) {
        //Ya existe un jugador con ese nombre por lo tanto no lo puedo agregar
        return;
    }
    players.insert(std::pair<std::string, PlayableCharacter>(name, factoryCharacters.create()));
}

void Game::movePlayer(const std::string& playerName, Offset offset) {
    players.at(playerName).move(offset);
}

void Game::addUpdatePosition(int x,int y) {
    Update update(x,y);
    updates.push_back(std::move(update));
}



Game::~Game() = default; /*{
    std::vector<Player*>::iterator it;
    for (it = players.begin(); it != players.end(); it++) {
        delete (*it);
    }
}*/
#include <iostream>
#include "Game.h"
#include "Factory.h"
#include "PlayableCharacter.h"
#include "Update.h"

Game::Game(std::string configFile): factoryCharacters(configFile), npcFactory(configFile) {
    MapFactory factory(configFile);
    map = factory.create();
}

void Game::createPlayer(const std::string& playerName, const std::string& charRace,
        const std::string& charClass) {
    factoryCharacters.create(map,playerName,charRace, charClass);
}

void Game::createNpc(const std::string& specie) {
    npcFactory.create(map,specie);
}

void Game::movePlayer(const std::string& playerName, Offset& offset) {
    map->triggerMove(playerName,offset);
}

void Game::attackNpc(const std::string& playerName, Position& position) {
    map->triggerAttack(playerName,position);
}

void Game::attackPlayer(const std::string& playerName, const std::string& playerNameEnemy) {
    map->triggerAttack(playerName,playerNameEnemy);
}

void Game::addUpdatePosition(int x,int y) {
    Update update(x,y);
    updates.push_back(update);
}

void Game::equipWeapon(Weapon* weapon, std::string playerName) {
    //aca habria que tener un factory que cree el arma segun el id que le pasan
    map->triggerEquipWeapon(playerName,weapon);
}

void Game::equipShield(std::string playerName, int minDef, int maxDef) {
    map->triggerEquipShield(playerName, minDef, maxDef);
}

Game::~Game() {
    delete map;
}

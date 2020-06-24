#include <iostream>
#include <Proxy/src/common_proxy_socket.h>
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
    factoryCharacters.create(this,map,playerName,charRace, charClass);
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

void Game::equipWeapon(Weapon* weapon, std::string playerName) {
    //aca habria que tener un factory que cree el arma segun el id que le pasan
    map->triggerEquipWeapon(playerName,weapon);
}

void Game::equipProtection(std::string playerName, Equippable element, int id) {
    map->triggerEquipProtection(playerName, element, id);
}

Game::~Game() {
    delete map;
}

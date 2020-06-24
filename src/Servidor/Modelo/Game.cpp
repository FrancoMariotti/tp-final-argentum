#include <iostream>
#include <Proxy/src/common_proxy_socket.h>
#include "Game.h"
#include "Factory.h"
#include "PlayableCharacter.h"
#include "Npc.h"
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
    PlayableCharacter *character = map->getPlayer(playerName);
    character->move(offset);
}

void Game::attackNpc(const std::string& playerName, Position& position) {
    Character* npc = map->findNpcAtPosition(position);
    if(!npc) return;
    PlayableCharacter *character = map->getPlayer(playerName);
    character->attack(npc);
}

void Game::attackPlayer(const std::string& playerName, const std::string& playerNameEnemy) {
    PlayableCharacter* enemy = map->getPlayer(playerNameEnemy);
    PlayableCharacter *character = map->getPlayer(playerName);
    character->attack(enemy);
}

void Game::equipWeapon(Weapon* weapon, std::string playerName) {
    //aca habria que tener un factory que cree el arma segun el id que le pasan
    PlayableCharacter *character = map->getPlayer(playerName);
    character->equipWeapon(weapon);
}

void Game::equipProtection(std::string playerName, Equippable element, int id) {
    PlayableCharacter *character = map->getPlayer(playerName);
    character->equipProtection(element,id);
}

Game::~Game() {
    delete map;
}

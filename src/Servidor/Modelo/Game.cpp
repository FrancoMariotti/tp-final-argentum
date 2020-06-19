#include "Game.h"
#include "Factory.h"
#include "PlayableCharacter.h"
#include "Update.h"

Game::Game(std::string configFile): factoryCharacters(configFile,map), npcFactory(configFile, map) {
    MapFactory factory(configFile);
    map = factory.create();
}

void Game::createPlayer(const std::string& playerName, const std::string& charRace,
        const std::string& charClass) {
    factoryCharacters.create(playerName,charRace, charClass);
}

void Game::createNpc(const std::string& specie) {
    npcFactory.create(specie);
}

void Game::movePlayer(const std::string& playerName, Offset& offset) {
    map.triggerMove(playerName,offset);
}

void Game::attackNpc(const std::string& playerName, Position& position) {
    map.triggerAttack(playerName,position);

}

void Game::addUpdatePosition(int x,int y) {
    Update update(x,y);
    updates.push_back(std::move(update));
}

void Game::equipWeapon(Weapon* weapon, std::string playerName) {
    //players.at(playerName).equipWeapon(weapon);
}

Game::~Game() {

}
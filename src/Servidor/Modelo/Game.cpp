#include <Proxy/src/common_message.h>
#include "Game.h"
#include "Factory.h"
#include "PlayableCharacter.h"
#include "Npc.h"
#include "Update.h"

Game::Game(std::string configFile): configFile(configFile), factoryCharacters(configFile)
    , npcFactory(configFile) {
    MapFactory factory(configFile);
    map = factory.create();
}

void Game::createPlayer(const std::string& playerName, const std::string& charRace,
        const std::string& charClass) {
    factoryCharacters.create(map,playerName,charRace, charClass, this);
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

void Game::equipProtection(std::string playerName, Equippable element, Equipment equipment) {
    PlayableCharacter *character = map->getPlayer(playerName);
    character->equipProtection(element,equipment);
}

void Game::initializeMapLayers(ProxySocket& pxySkt) {
    FileParser parser(configFile);
    Json::Value mapObj =  parser.read("map");
    int width_map = mapObj["width"].asInt();
    int height_map = mapObj["height"].asInt();
    std::vector<int> floorLayer;
    floorLayer.reserve(width_map*height_map);
    for (int j = 0; j < width_map*height_map ; ++j) {
         floorLayer.push_back(mapObj["layers"]["floor"]["data"][j].asInt());
    }
    std::vector<int> obstaclesLayer;
    obstaclesLayer.reserve(width_map*height_map);
    for (int j = 0; j < width_map*height_map ; ++j) {
         obstaclesLayer.push_back(mapObj["layers"]["obstacles"]["data"][j].asInt());
    }
    pxySkt.writeToClient(std::unique_ptr<Message> (
            new Draw("floor", floorLayer, width_map, height_map)));
    pxySkt.writeToClient(std::unique_ptr<Message> (
            new Draw("obstacles", obstaclesLayer, width_map, height_map)));
}

void Game::sendUpdates(ProxySocket& pxySkt) {
    while (!updates.empty()) {
        pxySkt.writeToClient(std::unique_ptr<Message> (
               updates.front()));
        updates.pop();
    }
}

void Game::movementUpdate(int x, int y) {
    updates.push(new Movement(x, y));
}

Game::~Game() {
    delete map;
}

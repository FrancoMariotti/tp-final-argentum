#include <Proxy/src/common_message.h>
#include "Game.h"
#include "Factory.h"
#include "PlayableCharacter.h"
#include "Npc.h"
#include "Update.h"

Game::Game(const std::string& configFile): configFile(configFile), factoryCharacters(configFile)
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
/*
void Game::equipWeapon(Weapon* weapon, const std::string& playerName) {
    //aca habria que tener un factory que cree el arma segun el id que le pasan
    PlayableCharacter *character = map->getPlayer(playerName);
    character->equipWeapon(weapon);
}
*/
void Game::equip(std::string playerName, int elementIndex) {
    PlayableCharacter *character = map->getPlayer(playerName);
    character->equip(elementIndex);
}

void Game::storeInInventory(std::string playerName, Equippable* element) {
    PlayableCharacter *character = map->getPlayer(playerName);
    character->store(element);
}

void Game::initializeMapLayers(ProxySocket& pxySkt) {
    FileParser parser(configFile);
    Json::Value mapObj =  parser.read("map");

    int width = mapObj["height"].asInt();
    int height = mapObj["width"].asInt();

    const Json::Value & floorLayersid = mapObj["layers"]["floor"]["data"];
    const Json::Value & obstaclesLayersid = mapObj["layers"]["obstacles"]["data"];

    std::vector<int> floorLayer;
    floorLayer.reserve(floorLayersid.size());

    for (const auto & i : floorLayersid){
        floorLayer.push_back(i.asInt());
    }

    std::vector<int> obstaclesLayer;
    obstaclesLayer.reserve(obstaclesLayersid.size());

    for (const auto & i : obstaclesLayersid){
        obstaclesLayer.push_back(i.asInt());
    }

    pxySkt.writeToClient(std::unique_ptr<Message> (
            new Draw("floor", floorLayer, width, height)));
    pxySkt.writeToClient(std::unique_ptr<Message> (
            new Draw("obstacles", obstaclesLayer, width, height)));
}

void Game::sendUpdates(/*ProxySocket& pxySkt*/) {
    ProxySocket sck;
    while (!updates.empty()) {
        Message* msg = updates.front();
        sck.writeToClient(std::unique_ptr<Message> (
              msg));
        //updates.pop();
        updates.pop();
        //delete msg;
    }
}

void Game::movementUpdate(int x, int y) {
    //updates.push(new Movement(x,y));
    updates.emplace(new Movement(x,y));
}

Game::~Game() {
    delete map;
}

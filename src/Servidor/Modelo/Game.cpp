#include <Proxy/src/common_message.h>

#include <utility>
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

void Game::equip(const std::string& playerName, int elementIndex) {
    PlayableCharacter *character = map->getPlayer(playerName);
    character->equip(elementIndex);
}

void Game::unequip(const std::string& playerName, int elementIndex) {
    PlayableCharacter *character = map->getPlayer(playerName);
    character->unequip(elementIndex);
}

void Game::storeInInventory(const std::string& playerName, Equippable* element) {
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

void Game::sendUpdates(ProxySocket& pxySkt) {
    //ProxySocket sck;
    while (!updates.empty()) {
        Message* msg = updates.front();
        pxySkt.writeToClient(std::unique_ptr<Message> (
              msg));
        updates.pop();
    }
}

void Game::drawUpdate(std::string id,std::vector<int> layer,int width,int height) {
    updates.push(new Draw(std::move(id), std::move(layer), width, height));
}

void Game::statsUpdate(float health_percentage,float mana_percentage,float exp_percentage,int gold,int level) {
    updates.push(new Stats(
            health_percentage,
            mana_percentage,
            exp_percentage,
            gold,level));
}

void Game::movementUpdate(int x, int y) {
    updates.push(new Movement(x,y));
}

Game::~Game() {
    delete map;
}

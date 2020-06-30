#include <Proxy/src/common_message.h>
#include "Game.h"
#include "Factory.h"
#include "PlayableCharacter.h"
#include "Npc.h"
#include "Update.h"

Game::Game(const std::string& configFile): configFile(configFile), factoryCharacters(configFile) {
    MapFactory factory(configFile);
    map = factory.create();
    map->update(this);
}

void Game::createPlayer(const std::string& playerName, const std::string& charRace,
        const std::string& charClass) {
    factoryCharacters.create(map,playerName,charRace, charClass, this);
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

void Game::initializeMap(ProxySocket& pxySkt) {
    map->sendLayers(pxySkt,configFile);
}

void Game::sendUpdates(ProxySocket& pxySkt) {
    while (!updates.empty()) {
        Message* msg = updates.front();
        pxySkt.writeToClient(std::unique_ptr<Message> (
              msg));
        updates.pop();
    }
}

void Game::spawnNpcUpdate(std::vector<spawn_character_t>& npcs) {
    updates.push(new SpawnNpc(npcs));
}

void Game::statsUpdate(float health_percentage,float mana_percentage,float exp_percentage,int gold,int level) {
    updates.push(new Stats(
            health_percentage,
            mana_percentage,
            exp_percentage,
            gold,level));
}

void Game::itemsUpdate(std::vector<std::string>& vector) {
    updates.push(new InventoryUpdate(vector));
}

void Game::movementUpdate(int x, int y) {
    updates.push(new Movement(x,y));
}

Game::~Game() {
    while(!updates.empty()) {
        delete updates.front();
        updates.pop();
    }
    delete map;
}

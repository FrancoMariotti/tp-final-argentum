#include <Proxy/src/common_message.h>
#include <thread>
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

void Game::updateModel() {
    map->moveNpcs();
}

/*void Game::start() {
    this->keep_playing = true;
    while(this->keep_playing) {
        //std::chrono
        //receive events
        //update model
        updateModel();
        //sleep(step)
        //sendUpdates()
        std::chrono::time_point<std::chrono::system_clock> start, end;
        start = std::chrono::system_clock::now();
        end = std::chrono::system_clock::now();
        int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
                (end-start).count();
        int gameloopDuration = elapsed_seconds;
        std::this_thread::sleep_for(std::chrono::seconds(gameloopDuration));
    }
}*/

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

void Game::notifySpawnNpcUpdate(std::vector<spawn_character_t>& npcs) {
    updates.push(new SpawnNpc(npcs));
}

void Game::notifyStatsUpdate(float health_percentage,float mana_percentage,float exp_percentage,int gold,int level) {
    updates.push(new Stats(
            health_percentage,
            mana_percentage,
            exp_percentage,
            gold,level));
}

void Game::notifyEquipmentUpdate(std::string weaponName, std::string armourName, std::string shieldName, std::string helmetName) {
    updates.push(new EquipmentUpdate(weaponName, armourName, shieldName, helmetName));
}
void Game::notifyItemsUpdate(std::vector<std::string> &vector) {
    updates.push(new InventoryUpdate(vector));

}

void Game::notifymovementUpdate(int x, int y) {
    updates.push(new Movement(x,y));
}

void Game::notifyMovementNpcUpdate(std::string idNpc, int x, int y) {
    updates.push(new MovementNpcUpdate(idNpc,x,y));
}

Game::~Game() {
    while(!updates.empty()) {
        delete updates.front();
        updates.pop();
    }
    delete map;
}

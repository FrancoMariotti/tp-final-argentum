#include "Common/common_proxy_socket.h"
#include <Common/Message.h>
#include <thread>
#include <utility>
#include "Game.h"
#include "Factory.h"
#include "PlayableCharacter.h"
#include "Npc.h"

Game::Game(const std::string& configFile, const std::string& playersInfoMapFile,
        const std::string& playersInfoFile): configFile(configFile), itemFactory()
    , mapFactory(configFile), map(mapFactory.create(&itemFactory)), commandExecutor(map),
    factoryCharacters(configFile, &itemFactory, playersInfoMapFile, playersInfoFile),
    npcFactory(configFile, &itemFactory) {}

void Game::updateModel(float looptime) {
    map->updateAllPlayers(looptime, this);
    map->moveNpcs(looptime);
    map->regenerateNpcs(looptime, npcFactory, this);
}

void Game::persistPlayersData(float loopTimeInSeconds) {
    map->persistPlayersData(factoryCharacters, loopTimeInSeconds);
}

std::queue<Message *> Game::initializeWorld() {
    std::queue<Message*> initializeMessages;
    map->addLayersTo(configFile, initializeMessages);
    map->initializeDropSpawns(initializeMessages);
    map->initializeNpcsSpawns(initializeMessages);
    map->initializePlayersSpawns(initializeMessages);
    return initializeMessages;
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

void Game::createNpc(const std::string& specie) {
    npcFactory.create(map,specie,this);
}

void Game::initialize() {
    //map->spawnCityCharacters(this);
    for(int i=0; i<4 ; i++) {
        createNpc("skeleton");
        createNpc("goblin");
        createNpc("spider");
        createNpc("zombie");
    }
}

/*void Game::initializeMap(ProxySocket& pxySkt) {
    map->sendLayers(pxySkt,configFile);
}*/

void Game::movePlayer(const std::string& playerName, Offset& offset) {
    PlayableCharacter *character = map->getPlayer(playerName);
    character->move(offset);
}

void Game::attack(const std::string &playerName, Position &position) {
    PlayableCharacter *character = map->getPlayer(playerName);
    Character* enemy = map->findCharacterAtPosition(position);
    if (enemy) character->attack(enemy);
}

void Game::equip(const std::string& playerName, int elementIndex) {
    PlayableCharacter *character = map->getPlayer(playerName);
    character->equip(elementIndex);
}

void Game::unequip(const std::string& playerName, int elementIndex) {
    PlayableCharacter *character = map->getPlayer(playerName);
    character->unequip(elementIndex);
}

/*void Game::storeInInventory(const std::string& playerName, Equippable* element) {
    PlayableCharacter *character = map->getPlayer(playerName);
    character->store(element);
}*/

bool Game::broadcastUpdateAvailable() {
    return !broadcastUpdates.empty();
}

Message* Game::nextBroadCastUpdate() {
    Message* msg = broadcastUpdates.front();
    broadcastUpdates.pop();
    return msg;
}

void Game::notifySpawnNpcUpdate(std::vector<location_t>& npcs) {
    broadcastUpdates.push(new SpawnStaticObjects(SPAWN_NPC_MESSAGE_ID,npcs));
}

void Game::notifySpawnPcUpdate(std::vector<spawn_playable_character_t> pcSpawns) {
    broadcastUpdates.push(new SpawnPc(pcSpawns));
}

void Game::notifyDropSpawnNUpdate(std::vector<location_t> dropSpawns) {
    broadcastUpdates.push(new SpawnStaticObjects(SPAWN_DROPS_MESSAGE_ID,dropSpawns));
}

void Game::notifyCityCharactersSpawn(std::vector<location_t> &spawns) {
    broadcastUpdates.push(new SpawnStaticObjects(SPAWN_CITY_CHARACTERS_MESSAGE_ID,spawns));
}

void Game::notifyStatsUpdate(float health_percentage,float mana_percentage,float exp_percentage,int gold,int level) {
    /*broadcastUpdates.push(new Stats(
            health_percentage,
            mana_percentage,
            exp_percentage,
            gold,level));*/
}

void Game::notifyEquipmentUpdate(std::string weaponName, std::string armourName, std::string shieldName, std::string helmetName) {
    //broadcastUpdates.push(new EquipmentUpdate(weaponName, armourName, shieldName, helmetName));
}
void Game::notifyItemsUpdate(std::vector<std::string> &vector) {
    //broadcastUpdates.push(new InventoryUpdate(vector));
}

void Game::notifymovementUpdate(std::string id,int x, int y) {
    broadcastUpdates.push(new Movement(std::move(id),x,y));
}

void Game::notifyMovementNpcUpdate(std::string idNpc, int x, int y) {
    //broadcastUpdates.push(new ActionUpdate(NPC_MOVEMENT_UPDATE_MESSAGE_ID,idNpc,x,y));
}

void Game::notifyConsoleOutputUpdate(std::vector<std::string> messages) {
    //broadcastUpdates.push(new ConsoleOutput(messages));
}

void Game::executeCommand(std::unique_ptr<Message>& command) {
    //std::string username = command->;
    std::string action = command->getCommand();
    int x = command->getX();
    int y = command->getY();
    commandExecutor.execute("franco",action,x,y);
}

Game::~Game() {
    while(!broadcastUpdates.empty()) {
        delete broadcastUpdates.front();
        broadcastUpdates.pop();
    }
    delete map;
}



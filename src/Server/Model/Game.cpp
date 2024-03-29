#include "Common/common_proxy_socket.h"
#include <Common/Messages/Message.h>
#include <thread>
#include <utility>
#include "Game.h"
#include "Factory.h"
#include "Server/Model/Character/PlayableCharacter.h"
#include "Server/Model/Character/Npc.h"
#include "Configuration.h"

Game::Game(const std::string& configFile, const std::string& playersInfoMapFile,
        const std::string& playersInfoFile): configFile(configFile), itemFactory()
    , mapFactory(configFile), map(mapFactory.create(&itemFactory)), commandExecutor(map),
    factoryCharacters(configFile, &itemFactory), npcFactory(configFile, &itemFactory),
    persistanceManager(playersInfoMapFile, playersInfoFile) {
    std::map<std::string, float> constants;
    FileParser parser(configFile);
    Json::Value constObj = parser.read("constants");
    for (auto &constant : constObj) {
        constants[constant["name"].asString()] = constant["value"].asFloat();
    }
    Configuration& config = Configuration::getInstance();
    config.constants = constants;
}

void Game::updateModel(float looptime) {
    map->updateAllPlayers(looptime, this);
    map->moveNpcs(looptime);
    map->regenerateNpcs(looptime, npcFactory, this);
}

void Game::persistPlayersData(float loopTimeInSeconds) {
    map->persistPlayersData(persistanceManager, loopTimeInSeconds);
}

std::queue<Message *> Game::initializeWorld() {
    std::queue<Message*> initializeMessages;
    map->addLayersTo(configFile, initializeMessages);
    map->initializeDropSpawns(initializeMessages);
    map->initializeNpcsSpawns(initializeMessages);
    map->updatePlayersSpawns(initializeMessages);
    return initializeMessages;
}

void Game::createPlayer(const std::string& playerName, const std::string& charRace,
        const std::string& charClass) {
    factoryCharacters.create(map, playerName, charRace, charClass,
            this, persistanceManager);
}

void Game::createNpc(const std::string& specie) {
    npcFactory.create(map,specie,this);
}

void Game::initialize() {
    for(int i=0; i<4 ; i++) {
        createNpc("skeleton");
        createNpc("goblin");
        createNpc("spider");
        createNpc("zombie");
    }
}

void Game::movePlayer(const std::string& playerName, Offset& offset) {
    PlayableCharacter *character = map->getPlayer(playerName);
    if (character) character->stopMeditating();
    character->move(offset);
}

void Game::attack(const std::string &playerName, Position &position) {
    PlayableCharacter *character = map->getPlayer(playerName);
    if (character) character->stopMeditating();
    Character* enemy = map->findCharacterAtPosition(position);
    if (enemy) character->attack(enemy);
}

void Game::equip(const std::string& playerName, int elementIndex) {
    PlayableCharacter *character = map->getPlayer(playerName);
    if (character) character->stopMeditating();
    character->equip(elementIndex);
}

void Game::unequip(const std::string& playerName, int elementIndex) {
    PlayableCharacter *character = map->getPlayer(playerName);
    character->unequip(elementIndex);
}

bool Game::directedUpdateAvailable() {
    return !directedUpdates.empty();
}

std::tuple<std::string,Message*> Game::nextDirectedUpdate() {
    std::tuple<std::string,Message*> msg = directedUpdates.front();
    directedUpdates.pop();
    return msg;
}

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

void Game::notifyDropSpawnNUpdate(std::vector<location_t> dropSpawns) {
    broadcastUpdates.push(new SpawnStaticObjects(SPAWN_DROPS_MESSAGE_ID,dropSpawns));
}

void Game::notifyCityCharactersSpawn(std::vector<location_t> &spawns) {
    broadcastUpdates.push(new SpawnStaticObjects(SPAWN_CITY_CHARACTERS_MESSAGE_ID,spawns));
}

void Game::notifyStatsUpdate(std::string& username,float health_percentage,float mana_percentage,float exp_percentage,int gold,int level) {
    directedUpdates.push(std::make_tuple(username,new Stats(
                                                        health_percentage,
                                                        mana_percentage,
                                                        exp_percentage,
                                                        gold,level)));
}

void Game::notifyEquipmentUpdate(std::string& username,std::string weaponName, std::string armourName, std::string shieldName, std::string helmetName) {
    broadcastUpdates.push(new EquipmentUpdate(username,weaponName, armourName, shieldName, helmetName));
}
void Game::notifyItemsUpdate(std::string& username,std::vector<std::string> &items) {
    directedUpdates.push(std::make_tuple(username,new InventoryUpdate(items)));
}

void Game::notifymovementUpdate(std::string id,int x, int y) {
    broadcastUpdates.push(new Movement(std::move(id),x,y));
}

void Game::notifyMovementNpcUpdate(std::string idNpc, int x, int y) {
    broadcastUpdates.push(new ActionUpdate(NPC_MOVEMENT_UPDATE_MESSAGE_ID,idNpc,x,y));
}

void Game::notifyConsoleOutputUpdate(std::string& username,std::vector<std::string> messages) {
    directedUpdates.push(std::make_tuple(username,new ConsoleOutput(messages)));
}

void Game::executeCommand(std::unique_ptr<Message>& msg) {
    command_t  command = msg->getCommand();
    PlayableCharacter *character = map->getPlayer(command.username);
    if (character) character->stopMeditating();
    commandExecutor.execute(command.username,command.input,command.x,command.y);
}

bool Game::login(const std::string &username, std::string &password) {
    return persistanceManager.login(username, password, map, this, factoryCharacters);
}

bool Game::existsUser(const std::string &username) {
    return persistanceManager.existsUser(username);
}

void Game::signup(const std::string &username, const std::string &password) {
    persistanceManager.signup(username, password);
}

std::queue<Message*> Game::disconnectPlayer(const std::string& username) {
    std::queue<Message*> pcSpawnsUpdate;
    map->disconnectPlayer(username, persistanceManager);
    map->updatePlayersSpawns(pcSpawnsUpdate);
    return pcSpawnsUpdate;
}

Game::~Game() {
    while(!broadcastUpdates.empty()) {
        delete broadcastUpdates.front();
        broadcastUpdates.pop();
    }
    delete map;
}

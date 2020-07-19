#include "Common/common_proxy_socket.h"
#include <Common/Message.h>
#include <thread>
#include <utility>
#include "Game.h"
#include "Factory.h"
#include "PlayableCharacter.h"
#include "Npc.h"
#include "Configuration.h"

//Configuration* Configuration::instance = 0;

Game::Game(const std::string& configFile, const std::string& playersInfoMapFile,
        const std::string& playersInfoFile): configFile(configFile), itemFactory()
    , mapFactory(configFile), map(mapFactory.create(&itemFactory)), commandExecutor(map),
    factoryCharacters(configFile, &itemFactory, playersInfoMapFile, playersInfoFile),
    npcFactory(configFile, &itemFactory) {
    std::map<std::string, float> constants;
    FileParser parser(configFile);
    Json::Value constObj = parser.read("constants");
    for (auto &constant : constObj) {
        constants[constant["name"].asString()] = constant["value"].asFloat();
    }
    Configuration& config = config.getInstance();
    config.constants = constants;
}

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
    map->updatePlayersSpawns(initializeMessages);
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
    for(int i=0; i<4 ; i++) {
        createNpc("skeleton");
        createNpc("goblin");
        createNpc("spider");
        createNpc("zombie");
    }
}

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
    commandExecutor.execute(command.username,command.input,command.x,command.y);
}

bool Game::login(const std::string &username, std::string &password) {
    return factoryCharacters.login(username, password, map, this);
}

std::queue<Message*> Game::disconnectPlayer(const std::string& username) {
    std::queue<Message*> pcSpawnsUpdate;
    map->disconnectPlayer(username, factoryCharacters);
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

bool Game::signup(const std::string &username, const std::string &password) {
    return factoryCharacters.signup(username, password);
}



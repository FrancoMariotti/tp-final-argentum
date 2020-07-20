#include <Common/common_proxy_socket.h>
#include <Common/Messages/Message.h>
#include <algorithm>
#include <utility>
#include "Map.h"
#include "Servidor/Modelo/Character/PlayableCharacter.h"
#include "Servidor/Modelo/Character/Npc.h"
#include "Servidor/Modelo/Factory.h"
#include "Common/Utils.h"
#include "Servidor/Modelo/Configuration.h"

Map::Map(int width,int height):width(width),height(height), lastNpcUpdate(0),
    lastPersistance(0), config(Configuration::getInstance()){}

void Map::add( Banker pBanker) {
    this->banker = std::move(pBanker);
}

void Map::add( Merchant pMerchant) {
    //this->merchant = std::move(pMerchant);
    merchant = pMerchant;
}

void Map::add( Priest pPriest) {
    //this->priest = std::move(pPriest);
    priest = pPriest;
}

void Map::add(City city) {
    cities.push_back(std::move(city));
}

void Map::registerCityCharactersSpawns(std::vector<location_t>& spawns) {
    for (auto &spawn : spawns) {
        cityCharactersSpawns.push_back(spawn);
    }
}

void Map::removePlayableCharacter(const std::string& playerName) {
    characters.erase(playerName);
}

void Map::add(const std::string& playerName, PlayableCharacter *character) {
    this->characters[playerName] = character;
}

void Map::add(std::string idNpc ,Npc* npc) {
    //npc->addMerchant(&merchant);
    this->npcs[idNpc] = npc;
}

void Map::add(const Obstacle& obstacle) {
    this->obstacles.push_back(obstacle);
}

void Map::removeNpc(const std::string& idNpc, Observer* observer) {
    npcs.erase(idNpc);
    updateNpcsSpawns(observer);
}

bool Map::isOccupied(Position pos) {
    auto itrCharacters = characters.begin();
    for (; itrCharacters != characters.end(); ++itrCharacters) {
        if(itrCharacters->second->collideWith(pos)) return true;
    }

    auto itrNpcs = npcs.begin();
    for (; itrNpcs != npcs.end(); ++itrNpcs) {
        if(itrNpcs->second->collideWith(pos)) return true;
    }

    auto itrObstacles = obstacles.begin();
    for (; itrObstacles != obstacles.end(); ++itrObstacles) {
        if((*itrObstacles).ocupies(pos)) return true;
    }

    return banker.ocupies(pos) || merchant.ocupies(pos) || priest.ocupies(pos);

}

bool Map::outOfBounds(Position position) const {
    return position.outOfBounds(0,height,0,width);
}

void Map::move(Position& from,Position& to) {
    if (!isOccupied(to) && !outOfBounds(to)) from = to;
}

Character* Map::findClosestCharacter(const Position& pos, int range) {
    int minDist = range;
    PlayableCharacter* enemy = nullptr;
    auto it = characters.begin();
    for (; it != characters.end(); ++it) {
        enemy = it->second->closestToInRange(pos, enemy, &minDist, range);
    }
    return enemy;
}

Character* Map::findCharacterAtPosition(Position &position) {
    Character* enemy = nullptr;
    for (auto &npc : npcs) {
        if (npc.second->collideWith(position)) enemy = npc.second;
    }
    if (!enemy) {
        for (auto &character : characters) {
            if (character.second->collideWith(position)) enemy = character.second;
        }
    }
    return enemy;
}

PlayableCharacter* Map::getPlayer(const std::string &playerName) {
    if (characters.find(playerName) != characters.end()) return characters.at(playerName);
    return nullptr;
}

void Map::addLayersTo(std::string configFile, std::queue<Message*>& initializeMessages) {
    FileParser parser(configFile);
    Json::Value mapObj =  parser.read("map");
    const Json::Value & floorLayersid = mapObj["layers"]["floor"]["data"];
    const Json::Value & obstaclesLayersid = mapObj["layers"]["obstacles"]["data"];
    std::vector<int> floorLayer;
    floorLayer.reserve(floorLayersid.size());

    for (const auto & i : floorLayersid){
        floorLayer.push_back(i.asInt());
    }

    initializeMessages.push(new Draw("floor",floorLayer,width,height));
    initializeMessages.push(new SpawnStaticObjects(SPAWN_CITY_CHARACTERS_MESSAGE_ID,
                                                                cityCharactersSpawns));
    std::vector<int> obstaclesLayer;
    obstaclesLayer.reserve(obstaclesLayersid.size());

    for (const auto & i : obstaclesLayersid){
        obstaclesLayer.push_back(i.asInt());
    }

    initializeMessages.push(new Draw("obstacles",obstaclesLayer,width,height));
}

void Map::initializeDropSpawns(std::queue<Message*>& initializeMessages) {
    initializeMessages.push(new SpawnStaticObjects(SPAWN_DROPS_MESSAGE_ID,
                                                                dropsSpawns));
}

Position Map::asignRandomPosition() {
    int x, y;
    x = Utils::random_int_number(0, height - 1);
    y = Utils::random_int_number(0, width - 1);
    while (isOccupied(Position(x, y))) {
        x = Utils::random_int_number(0, height - 1);
        y = Utils::random_int_number(0, width - 1);
    }
    return Position(x, y);
}

Position Map::asignRandomPosInAnyCity() {
    int randomCityIndex = Utils::random_int_number(0, cities.size() - 1);
    return cities[randomCityIndex].getRandomPos(this);
}

void Map::moveNpcs(float looptime) {
    auto itrNpcs = npcs.begin();
    for (; itrNpcs != npcs.end(); itrNpcs++) {
        itrNpcs->second->move(looptime);
    }
}

void Map::updateAllPlayers(float looptime, Observer* observer) {
    auto itrCharacters = characters.begin();
    for (; itrCharacters != characters.end(); itrCharacters++) {
        itrCharacters->second->recoverMana(looptime);
        itrCharacters->second->recoverLifePoints(looptime);
        itrCharacters->second->recoverManaMeditating(looptime);
    }
    //Quizas aca deberiamos tambien updatear todos los equipamentos y posiciones de
    // todos los players del mapa, ver como resolver esto
    //updatePcSpawns(observer);
}

void Map::addDrop(Drop drop) {
    drops.push_back(drop);
    location_t dropSpawn = {drop.getPosition().getX(), drop.getPosition().getY(), drop.getName()};
    dropsSpawns.push_back(dropSpawn);
}

Drop Map::takeDropFromPos(Position position) {
    auto it = drops.begin();
    for (;it != drops.end(); it++) {
        if (it->getPosition() == position) {
            Drop drop = *it;
            drops.erase(std::remove_if(drops.begin(),
                                       drops.end(),
                                       [position](Drop drop){
                                           return drop.getPosition() == position;
                                       }),
                        drops.end());
            dropsSpawns.erase(std::remove_if(dropsSpawns.begin(),
                                                dropsSpawns.end(),
                                             [position](location_t location){
                                                 return Position(location.x,location.y) == position;
                                             }));
            return drop;
        }
    }
    return Drop();
}

void Map::updateDropSpawns(Observer *observer) {
    observer->notifyDropSpawnNUpdate(dropsSpawns);
}

bool Map::posInCity(Position position) {
    for (auto & city : cities) {
        if (city.ocupies(position)) return true;
    }
    return false;
}

Priest *Map::getPriestAtPosition(const Position& position) {
    if (priest.ocupies(position)) return &priest;
    return nullptr;
}


Banker* Map::getBankerAtPosition(const Position& position) {
    if (banker.ocupies(position)) return &banker;
    return nullptr;
}

Position Map::getRandomPosAtClosestPriestCity(PlayableCharacter *player) {
    Position nearestPriestPos = priest.closestPositionTo(player);

    Position randomPos(0,0);

    for (City & city : cities) {
        if(city.ocupies(nearestPriestPos)) {
            randomPos = city.getRandomPos(this);
        }
    }

    return randomPos;
}

Merchant *Map::getMerchantAtPosition(Position position) {
    if (merchant.ocupies(position)) return &merchant;
    return nullptr;
}

void Map::reviveIn(PlayableCharacter *player, Position position) {
    priest.reviveIn(player,position);
}

bool Map::hasDropInPos(Position position) {
    for (auto &drop : drops) {
        if (drop.getPosition() == position) return true;
    }
    return false;
}

void Map::regenerateNpcs(float loopTimeInSeconds, NpcFactory& npcFactory, Observer* observer) {
    if (lastNpcUpdate + loopTimeInSeconds >= config.constants["timeToRespawnNpcs"]
        && npcs.size() < (unsigned)config.constants["npcsAmount"]) {
        std::vector<std::string> species = {"goblin", "spider", "zombie", "skeleton"};
        int randomIndex = Utils::random_int_number(0, species.size() - 1);
        npcFactory.create(this, species[randomIndex], observer);
        lastNpcUpdate = 0;
        updateNpcsSpawns(observer);
    } else {
        lastNpcUpdate += loopTimeInSeconds;
    }
}

void Map::persistPlayersData(PersistanceManager& pManager, float loopTImeInSeconds) {
    if (lastPersistance + loopTImeInSeconds >= config.constants["timeToPersist"]) {
        lastPersistance = 0;
        std::cout << "Guardando informacion de los jugadores" << std::endl;
        for (auto &pc : characters) {
            pManager.persistPlayerData(pc.second);
        }
    } else {
        lastPersistance += loopTImeInSeconds;
    }
}

void Map::initializeNpcsSpawns(std::queue<Message*>& initializeMessages) {
    std::vector<location_t> npcSpawns;
    for (auto &npc : npcs) {
        npc.second->addSpawnInfoTo(npcSpawns);
    }
    initializeMessages.push(new SpawnStaticObjects(SPAWN_NPC_MESSAGE_ID,npcSpawns));
}

void Map::updateNpcsSpawns(Observer* observer) {
    std::vector<location_t> npcSpawns;
    for (auto &npc : npcs) {
        npc.second->addSpawnInfoTo(npcSpawns);
    }
    observer->notifySpawnNpcUpdate(npcSpawns);
}

void Map::updatePlayersSpawns(std::queue<Message*>& initializeMessages) {
    std::vector<spawn_playable_character_t> pcSpawns;
    for (auto &pc : characters) {
        pc.second->addSpawnInfoTo(pcSpawns);
    }
    initializeMessages.push(new SpawnPc(pcSpawns));
}

bool Map::empty() {
    return characters.empty();
}

void Map::disconnectPlayer(const std::string& username, PersistanceManager& pManager) {
    PlayableCharacter* player = getPlayer(username);
    if (player) {
        pManager.persistPlayerData(player);
        removePlayableCharacter(username);
    }
}

Map::~Map() {
    auto itrNpcs = npcs.begin();
    for (; itrNpcs != npcs.end(); itrNpcs++) {
        delete itrNpcs->second;
    }

    auto itCharacters = characters.begin();
    for (; itCharacters != characters.end(); itCharacters++) {
        delete itCharacters->second;
    }
}


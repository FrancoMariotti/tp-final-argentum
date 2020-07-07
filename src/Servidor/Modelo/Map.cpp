#include <Proxy/src/common_proxy_socket.h>
#include <Proxy/src/common_message.h>
#include <algorithm>
#include <utility>
#include "Map.h"
#include "PlayableCharacter.h"
#include "Npc.h"
#include "Factory.h"
#include "Servidor/Common/Utils.h"

#define NPCSAMOUNT 16

Map::Map(int width,int height):width(width),height(height), lastNpcUpdate(0){}

void Map::add( Banker pBanker) {
    this->banker = std::move(pBanker);
}

void Map::add( Merchant pMerchant) {
    this->merchant = std::move(pMerchant);
}

void Map::add( Priest pPriest) {
    this->priest = std::move(pPriest);
}

void Map::add(City city) {
    cities.push_back(std::move(city));
}

void Map::registerCityCharactersSpawns(std::vector<spawn_character_t>& spawns) {
    for (auto &spawn : spawns) {
        cityCharactersSpawns.push_back(spawn);
    }
}

void Map::removePlayableCharacter(const std::string& playerName) {
    characters.erase(playerName);
}

void Map::add(const std::string& playerName, PlayableCharacter *character) {
    this->characters[playerName] = character;
    //Esto lo agrego para que el personaje se renderice en la posicion inicial
    Offset nullOffset (0, 0);
    character->move(nullOffset);
}

void Map::add(std::string idNpc ,Npc* npc) {
    npc->addMerchant(&merchant);
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
        /*if(it->second->isDead()) continue;
        int currDist = it->second->distanceTo(pos);
        if (currDist <= range && currDist <= minDist) {
            minDist = currDist;
            enemy = it->second;
        }*/
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
    return characters.at(playerName);
}

void Map::sendLayers(ProxySocket& sck,const std::string& configFile) const {
    FileParser parser(configFile);
    Json::Value mapObj =  parser.read("map");

    const Json::Value & floorLayersid = mapObj["layers"]["floor"]["data"];
    const Json::Value & obstaclesLayersid = mapObj["layers"]["obstacles"]["data"];

    std::vector<int> floorLayer;
    floorLayer.reserve(floorLayersid.size());

    for (const auto & i : floorLayersid){
        floorLayer.push_back(i.asInt());
    }

    sck.writeToClient(std::unique_ptr<Message> (
              new Draw("floor",floorLayer,width,height)));

    sck.writeToClient(std::unique_ptr<Message> (
            new SpawnCityCharacters(cityCharactersSpawns)));

    std::vector<int> obstaclesLayer;
    obstaclesLayer.reserve(obstaclesLayersid.size());

    for (const auto & i : obstaclesLayersid){
        obstaclesLayer.push_back(i.asInt());
    }
    sck.writeToClient(std::unique_ptr<Message> (
              new Draw("obstacles",obstaclesLayer,width,height)));
}

//METODO A USAR EN NUEVA COMUNICACION
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

    initializeMessages.push(new SpawnCityCharacters(cityCharactersSpawns));

    std::vector<int> obstaclesLayer;
    obstaclesLayer.reserve(obstaclesLayersid.size());

    for (const auto & i : obstaclesLayersid){
        obstaclesLayer.push_back(i.asInt());
    }
    initializeMessages.push(new Draw("obstacles",obstaclesLayer,width,height));
}

void Map::initializeDropSpawns(std::queue<Message*>& initializeMessages) {
    initializeMessages.push(new SpawnDrops(dropsSpawns));

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
    }
    //Quizas aca deberiamos tambien updatear todos los equipamentos y posiciones de
    // todos los players del mapa, ver como resolver esto
    /*std::vector<spawn_playable_character_t> pcSpawns;
    for (auto &pc : characters) {
        pc.second->addSpawnInfoTo(pcSpawns);
    }
    observer->notifySpawnPcUpdate(pcSpawns);*/
}

void Map::addDrop(Drop drop) {
    drops.push_back(drop);
    spawn_character_t dropSpawn = {drop.getPosition().getX(), drop.getPosition().getY(), drop.getName()};
    dropsSpawns.push_back(dropSpawn);
}

Drop Map::takeDropFromPos(Position position) {
    for (unsigned int i = 0; i < drops.size(); i++) {
        if (drops[i].getPosition() == position) {
            //QUIZAS DEBO REDEFINIR EL OPERADOR IGUAL PARA QUE MUEVA EL PUNTERO AL EQUIPABLE Y NO SE BORRE DE MEMORIA
            Drop drop = drops[i];
            drops.erase(drops.begin() + i);
            for (unsigned int j = 0; j < dropsSpawns.size(); ++j) {
                if (Position(dropsSpawns[i].x, dropsSpawns[i].y)  == drop.getPosition()) {
                    dropsSpawns.erase(dropsSpawns.begin() + i);
                }
            }
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

void Map::regenerateNpcs(float loopTimeInSeconds, NpcFactory& npcFactory, Observer* observer) {
    if (lastNpcUpdate + loopTimeInSeconds >= 30 && npcs.size() < NPCSAMOUNT) {
        std::vector<std::string> species = {"goblin", "spider", "zombie", "skeleton"};
        int randomIndex = Utils::random_int_number(0, species.size() - 1);
        npcFactory.create(this, species[randomIndex], observer);
        lastNpcUpdate = 0;
        updateNpcsSpawns(observer);
    } else {
        lastNpcUpdate += loopTimeInSeconds;
    }
}

void Map::initializeNpcsSpawns(std::queue<Message*>& initializeMessages) {
    std::vector<spawn_character_t> npcSpawns;
    for (auto &npc : npcs) {
        npc.second->addSpawnInfoTo(npcSpawns);
    }
    initializeMessages.push(new SpawnNpc(npcSpawns));
}

void Map::updateNpcsSpawns(Observer* observer) {
    std::vector<spawn_character_t> npcSpawns;
    for (auto &npc : npcs) {
        npc.second->addSpawnInfoTo(npcSpawns);
    }
    observer->notifySpawnNpcUpdate(npcSpawns);
}

void Map::initializePlayersSpawns(std::queue<Message*>& initializeMessages) {
    std::vector<spawn_playable_character_t> pcSpawns;
    for (auto &pc : characters) {
        pc.second->addSpawnInfoTo(pcSpawns);
    }
    initializeMessages.push(new SpawnPc(pcSpawns));
}

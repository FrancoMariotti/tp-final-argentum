#include <Proxy/src/common_proxy_socket.h>
#include <Proxy/src/common_message.h>
#include <algorithm>
#include "Map.h"
#include "PlayableCharacter.h"
#include "Npc.h"
#include "Factory.h"
#include "Servidor/Common/Utils.h"

#define NPCSAMOUNT 16


Map::Map() {
    this->width = 0;
    this->height = 0;
}

Map::Map(const std::string& configFile,int width,int height):width(width),
    height(height) {}

void Map::registerNpcSpawn(Observer * observer,spawn_character_t spawn) {
    npcSpawns.push_back(spawn);
    if(npcSpawns.size() == NPCSAMOUNT) {
        observer->notifySpawnNpcUpdate(npcSpawns);
    }
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
}

void Map::add(std::string idNpc ,Npc* npc) {
    this->npcs[idNpc] = npc;
}

void Map::add(City city) {
    cities.push_back(std::move(city));
}

void Map::add(const Obstacle& obstacle) {
    this->obstacles.push_back(obstacle);
}

void Map::removeNpc(const std::string& idNpc, Observer* observer) {
    npcs.erase(idNpc);
    npcSpawns.erase(std::remove_if(npcSpawns.begin(),
                              npcSpawns.end(),
                              [idNpc](spawn_character_t npc){return npc.id == idNpc;}),
               npcSpawns.end());
    observer->notifySpawnNpcUpdate(npcSpawns);
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

    for (auto &city : cities) {
        if (city.isOcupied(pos)) return true;
    }

    return false;
}

void Map::move(Position& from,Position& to) {
    bool outOfBounds = to.outOfBounds(0,height,0,width);
    if (!isOccupied(to) && !outOfBounds) from = to;
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

    std::vector<int> obstaclesLayer;
    obstaclesLayer.reserve(obstaclesLayersid.size());

    for (const auto & i : obstaclesLayersid){
        obstaclesLayer.push_back(i.asInt());
    }
    sck.writeToClient(std::unique_ptr<Message> (
              new Draw("obstacles",obstaclesLayer,width,height)));
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

void Map::moveNpcs(float looptime) {
    auto itrNpcs = npcs.begin();
    for (; itrNpcs != npcs.end(); itrNpcs++) {
        itrNpcs->second->move(looptime);
    }
}

void Map::updateAllPlayers(float looptime) {
    auto itrCharacters = characters.begin();
    for (; itrCharacters != characters.end(); itrCharacters++) {
        itrCharacters->second->recoverMana(looptime);
        itrCharacters->second->recoverLifePoints(looptime);
    }
}

void Map::addDrop(Drop drop) {

}

bool Map::posInCity(Position position) {
    for (auto & city : cities) {
        if (city.ocupies(position)) return true;
    }
    return false;
}

void Map::depositInBank(PlayableCharacter *player,const Position& position,const std::string& element) {
    for (City & city : cities) {
        city.depositInBank(position,player,element);
    }
}

void Map::depositInBank(PlayableCharacter *player,const Position& position,int gold_amount) {
    for (City & city : cities) {
        city.depositInBank(position,player,gold_amount);
    }
}

void Map::searchPriestToRevive(PlayableCharacter *character, Position position) {
    for (City & city : cities) {
        city.searchPriestToRevive(character, position);
    }
}

void Map::reviveNextToClosestPriest(PlayableCharacter *character) {
    int minDistance = -1;
    int currDistance;
    City* nearestCity = nullptr;
    for (City & city : cities) {
        currDistance = city.distanceToPriest(character);
        if (minDistance < 0 || currDistance < minDistance) {
            minDistance = currDistance;
            nearestCity = &city;
        }
    }
    nearestCity->revivePlayerHere(character, this);
}

void Map::extractFromBank(PlayableCharacter *player, const Position& position, int goldAmount) {
    for (City & city : cities) {
        city.extractFromBank(position,player,goldAmount);
    }
}

void Map::extractFromBank(PlayableCharacter *player, const Position& position, const std::string& element) {
    for (City & city : cities) {
        city.extractFromBank(position,player,element);
    }
}

void Map::spawnCityCharacters(Observer *observer) {
    observer->notifyCityCharactersSpawn(cityCharactersSpawns);
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











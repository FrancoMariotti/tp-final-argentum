#include <Proxy/src/common_proxy_socket.h>
#include <Proxy/src/common_message.h>
#include "Map.h"
#include "PlayableCharacter.h"
#include "Npc.h"
#include "Factory.h"
#include "Servidor/Common/Utils.h"

Map::Map():npcFactory("") {
    this->width = 0;
    this->height = 0;
}

Map::Map(std::string configFile,int width,int height):width(width),height(height),npcFactory(configFile) {}


void Map::registerNpcSpawn(spawn_character_t spawn) {
    spawns.push_back(spawn);
}

void Map::update(Observer* observer) {
    for(int i=0; i<4 ; i++) {
        npcFactory.create(this,"spider",observer);
    }
    observer->spawnNpcUpdate(spawns);
}
void Map::addPlayableCharacter(const std::string& playerName, PlayableCharacter *character) {
    this->characters[playerName] = character;
}

void Map::addNpc(Npc* npc) {
    this->npcs.push_back(npc);
}

void Map::addObstacle(Obstacle* obstacle) {
    this->obstacles.push_back(obstacle);
}

bool Map::isOccupied(Position pos) {
    auto itrCharacters = characters.begin();
    for (; itrCharacters != characters.end(); ++itrCharacters) {
        if(itrCharacters->second->collideWith(pos)) return true;
    }

    auto itrNpcs = npcs.begin();
    for (; itrNpcs != npcs.end(); ++itrNpcs) {
        if((*itrNpcs)->collideWith(pos)) return true;
    }

    auto itrObstacles = obstacles.begin();
    for (; itrObstacles != obstacles.end(); ++itrObstacles) {
        if((*itrObstacles)->ocupies(pos)) return true;
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
        int currDist = it->second->distanceTo(pos);
        if (currDist <= range && currDist <= minDist) {
            minDist = currDist;
            enemy = it->second;
        }
    }
    return enemy;
}

Character* Map::findNpcAtPosition(Position &position) {
    Npc* enemy = nullptr;
    auto itrNpcs = npcs.begin();
    for (; itrNpcs != npcs.end(); ++itrNpcs) {
        if((*itrNpcs)->collideWith(position)) enemy = *itrNpcs;
    }
    return enemy;
}

PlayableCharacter *Map::getPlayer(const std::string &playerName) {
    return characters.at(playerName);
}

Map::~Map() {
    std::vector<Npc*>::iterator itrNpcs;
    for (itrNpcs = npcs.begin(); itrNpcs != npcs.end(); itrNpcs++) {
        delete (*itrNpcs);
    }

    std::map<std::string,PlayableCharacter*>::iterator itCharacters;
    for (itCharacters = characters.begin(); itCharacters != characters.end(); itCharacters++) {
        delete itCharacters->second;
    }

    std::vector<Obstacle*>::iterator itrObstacles;
    for (itrObstacles = obstacles.begin(); itrObstacles != obstacles.end(); ++itrObstacles) {
        delete (*itrObstacles);
    }
}
void Map::sendLayers(ProxySocket& sck,std::string configFile) const {
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





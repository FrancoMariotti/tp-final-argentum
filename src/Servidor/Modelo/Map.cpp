#include <memory>
#include "Map.h"
#include "PlayableCharacter.h"
#include "Npc.h"

Map::Map() = default;

Map::Map(int width,int height):width(width),height(height) {}

void Map::addPlayableCharacter(std::string playerName, PlayableCharacter *character) {
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

bool Map::outOfBounds(Position &position) const {
    return position.outOfBounds(0,height,0,width);
}


void Map::move(Position& from,Position& to) {
    //if(outOfBounds(to)) return;
    if (!isOccupied(to) && !outOfBounds(to)) from = to;
}

Character* Map::findClosestCharacter(Position pos, int range) {
    int minDist = range;
    PlayableCharacter* enemy = NULL;
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




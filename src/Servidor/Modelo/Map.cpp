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

bool Map::outOfBounds(Position &position) {
    return position.outOfBounds(0,height,0,width);
}


void Map::move(Position& from,Position& to) {
    if(outOfBounds(to)) return;
    if (!isOccupied(to)) from = to;
}

Character* Map::findClosestCharacter(Position pos, int range) {
    //EL MAPA DEBERIA TEENR UN VECTOR CON TODOS LOS PERSONAJES JUGABLES,ESE VECTOR ES CHARATERS
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

void Map::triggerMove(const std::string &playerName, Offset &offset) {
    characters.at(playerName)->move(this,offset);
}

Npc* Map::findNpcAtPosition(Position &position) {
    auto itrNpcs = npcs.begin();
    for (; itrNpcs != npcs.end(); ++itrNpcs) {
        if((*itrNpcs)->collideWith(position)) return *itrNpcs;
    }
    return NULL;
}

void Map::triggerAttack(const std::string &playerName, Position &position) {
    Npc* npc = findNpcAtPosition(position);
    if(!npc) return;
    characters.at(playerName)->attack(npc);
}

void Map::triggerAttack(const std::string &playerName, const std::string &playerNameEnemy) {
    PlayableCharacter* enemy = characters.at(playerNameEnemy);
    characters.at(playerName)->attack(enemy);
}

void Map::triggerEquipWeapon(const std::string &playerName,Weapon *weapon) {
    characters.at(playerName)->equipWeapon(weapon);
}

void Map::triggerEquipProtection(std::string playerName, Equippable element, int id) {
    characters.at(playerName)->equipProtection(element, id);
}

Map::~Map() {
    std::map<std::string,PlayableCharacter*>::iterator itCharacters;
    for (itCharacters = characters.begin(); itCharacters != characters.end(); itCharacters++) {
        delete itCharacters->second;
    }

    std::vector<Obstacle*>::iterator itrObstacles;
    for (itrObstacles = obstacles.begin(); itrObstacles != obstacles.end(); ++itrObstacles) {
        delete (*itrObstacles);
    }

    std::vector<Npc*>::iterator itrNpcs;
    for (itrNpcs = npcs.begin(); itrNpcs != npcs.end(); itrNpcs++) {
        delete (*itrNpcs);
    }
}




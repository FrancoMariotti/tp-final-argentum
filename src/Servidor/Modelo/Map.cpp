#include "Map.h"
#include "PlayableCharacter.h"
#include "Npc.h"

Map::Map() = default;

Map::Map(int width,int height):width(width),height(height) {}

void Map::addPlayableCharacter(PlayableCharacter* character) {
    this->characters.push_back(character);
}

void Map::addNpc(Npc* npc) {
    this->npcs.push_back(npc);
}

void Map::addObstacle(Obstacle* obstacle) {
    this->obstacles.push_back(obstacle);
}

bool Map::isOccupied(Position pos) {
    std::vector<PlayableCharacter*>::iterator itrCharacters;
    for (itrCharacters = characters.begin() ; itrCharacters != characters.end(); ++itrCharacters) {
        if((*itrCharacters)->collideWith(pos)) return true;
    }

    std::vector<Npc*>::iterator itrNpcs;
    for (itrNpcs = npcs.begin() ; itrNpcs != npcs.end(); ++itrNpcs) {
        if((*itrNpcs)->collideWith(pos)) return true;
    }

    std::vector<Obstacle*>::iterator itrObstacles;
    for (itrObstacles = obstacles.begin() ; itrObstacles != obstacles.end(); ++itrObstacles) {
        if((*itrObstacles)->ocupies(pos)) return true;
    }
    return false;
}

void Map::move(Position& from,Position& to) {
   /*
    //estaria bueno tener un solo iterador que recorra ambas listas.
    std::vector<PlayableCharacter*>::iterator itrCharacters;
    for (itrCharacters = characters.begin() ; itrCharacters != characters.end(); ++itrCharacters) {
        if((*itrCharacters)->collideWith(to)) return;
    }

    std::vector<Npc*>::iterator itrNpcs;
    for (itrNpcs = npcs.begin() ; itrNpcs != npcs.end(); ++itrNpcs) {
        if((*itrNpcs)->collideWith(to)) return;
    }

    std::vector<Obstacle*>::iterator itrObstacles;
    for (itrObstacles = obstacles.begin() ; itrObstacles != obstacles.end(); ++itrObstacles) {
        if((*itrObstacles)->ocupies(to)) return;
    }
    */
    if (!isOccupied(to)) from = to;
}


Character* Map::findClosestCharacter(Position pos, int range) {
    //EL MAPA DEBERIA TEENR UN VECTOR CON TODOS LOS PERSONAJES JUGABLES,ESE VECTOR ES CHARATERS
    int minDist = range;
    PlayableCharacter* enemy = NULL;
    std::vector<PlayableCharacter*>::iterator it;
    for (it = characters.begin() ; it != characters.end(); ++it) {
        int currDist = (*it)->distanceTo(pos);
        if (currDist <= range && currDist <= minDist) {
            minDist = currDist;
            enemy = (*it);
        }
    }
    return enemy;
}

Map::~Map() {
    std::vector<Obstacle*>::iterator itrObstacles;
    for (itrObstacles = obstacles.begin() ; itrObstacles != obstacles.end(); ++itrObstacles) {
        delete *itrObstacles;
    }
}

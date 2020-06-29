#ifndef ARGENTUM_MAPA_H
#define ARGENTUM_MAPA_H

#include "map"
#include "vector"
#include "Position.h"
#include "Obstacle.h"
#include "Weapon.h"
#include "Equippable.h"
#include "Observer.h"

class Character;
class Npc;
class PlayableCharacter;
class Weapon;

class Map {
    int width;
    int height;
    std::map<std::string,PlayableCharacter*> characters;
    std::vector<Npc*> npcs;
    std::vector<Obstacle*> obstacles;
    public:
        Map();
        Map(int width,int height);
        void addPlayableCharacter(const std::string& playerName,PlayableCharacter* character);
        void addNpc(Npc* npc);
        void addObstacle(Obstacle* obstacle);
        bool isOccupied(Position pos);
        void move(Position& from,Position& to);
        Character* findNpcAtPosition(Position &position);
        Character* findClosestCharacter(const Position& pos, int range);
        PlayableCharacter *getPlayer(const std::string &basicString);
        void sendLayers(Observer *observer,std::string configFile) const;
        ~Map();

    Position asignRandomPosition();
};

#endif //ARGENTUM_MAPA_H

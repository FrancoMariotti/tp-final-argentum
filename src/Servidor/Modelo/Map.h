#ifndef ARGENTUM_MAPA_H
#define ARGENTUM_MAPA_H
#include "map"
#include "vector"
#include "Position.h"
#include "Obstacle.h"
#include "Weapon.h"

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
    Npc* findNpcAtPosition(Position &position);
    public:
        Map();
        Map(int width,int height);
        void addPlayableCharacter(std::string playerName,PlayableCharacter* character);
        void addNpc(Npc* npc);
        void addObstacle(Obstacle* obstacle);
        bool isOccupied(Position pos);
        void move(Position& from,Position& to);
        void triggerMove(const std::string &playerName, Offset &offset);
        void triggerAttack(const std::string& playerName,Position& position);
        void triggerEquipWeapon(const std::string &playerName,Weapon *weapon);
        Character* findClosestCharacter(Position pos, int range);
        ~Map();
};

#endif //ARGENTUM_MAPA_H

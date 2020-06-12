#ifndef ARGENTUM_MAPA_H
#define ARGENTUM_MAPA_H

#include "vector"
#include "Position.h"
#include "Obstacle.h"

class GameObject;
class Npc;
class PlayableCharacter;

class Map {
    int width;
    int height;
    std::vector<Npc*> npcs;
    std::vector<PlayableCharacter*> characters;
    std::vector<Obstacle*> obstacles;
    public:
        Map(int width,int height);
        void addPlayableCharacter(PlayableCharacter* character);
        void addNpc(Npc* npc);
        void addObstacle(Obstacle* obstacle);
        void move(Position& from,Position& to);
        GameObject* findClosestCharacter(Position pos, int range);
        ~Map();
};

#endif //ARGENTUM_MAPA_H

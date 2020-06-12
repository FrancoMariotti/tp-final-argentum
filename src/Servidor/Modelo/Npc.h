//
// Created by franco on 10/6/20.
//

#ifndef ARGENTUM_NPC_H
#define ARGENTUM_NPC_H

#include "Map.h"
#include "GameObject.h"
#include "Mobility.h"

class Mobility;
class Map;

class Npc : public GameObject {
private:
    int lifePoints;
    Mobility *mobility;
    //std::vector<Personaje*> &characters;
    //Criatura criatura
public:
    Npc(int lifePoints, Mobility *mobility, int x, int y, Map &map);
    Offset findClosestCharacterOffset();
    void move();
    ~Npc();
};



#endif //ARGENTUM_NPC_H

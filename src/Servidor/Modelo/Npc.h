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
    //Criatura criatura
public:
    //Pasamos la Mobility por parametro porque pensamos en que puede
    //haber npcs que se muevan y otros que no.
    Npc(int lifePoints, Mobility *mobility, int x, int y, Map &map);
    Offset findClosestCharacterOffset();
    void move();
    ~Npc();
};



#endif //ARGENTUM_NPC_H

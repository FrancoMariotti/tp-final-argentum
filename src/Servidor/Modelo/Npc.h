//
// Created by franco on 10/6/20.
//

#ifndef ARGENTUM_NPC_H
#define ARGENTUM_NPC_H

#include "Map.h"
#include "Character.h"
#include "Mobility.h"
#include "StrategyMoveNPC.h"

class Mobility;
class Map;

class Npc : public Character {
private:
    int lifePoints;
    Mobility *mobility;
    //Criatura criatura
    StrategyMoveNPC movement;
public:
    //Pasamos la Mobility por parametro porque pensamos en que puede
    //haber npcs que se muevan y otros que no.
    Npc(int lifePoints, Mobility *mobility, int x, int y, Map &map);
    void move();
    ~Npc();
};



#endif //ARGENTUM_NPC_H

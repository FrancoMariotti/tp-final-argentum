//
// Created by franco on 10/6/20.
//

#ifndef ARGENTUM_NPC_H
#define ARGENTUM_NPC_H

#include "Map.h"
#include "Character.h"
#include "Mobility.h"
#include <string>

class Mobility;
class Map;

class Npc : public Character {
private:
    Mobility *mobility;
    //POR AHORA LO PLANTEO COMO UN STRING
    std::string specie;
public:
    //Pasamos la Mobility por parametro porque pensamos en que puede
    //haber npcs que se muevan y otros que no.
    Npc(int lifePoints, Mobility *mobility, int x, int y, Map *map,int constitution,
        int strength,int agility,int intelligence, int lvl, std::string specie);
    void move();
    virtual void attack(Character* character) override;
    ~Npc() override;
};



#endif //ARGENTUM_NPC_H

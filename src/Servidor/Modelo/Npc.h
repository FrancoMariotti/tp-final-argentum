//
// Created by franco on 10/6/20.
//

#ifndef ARGENTUM_NPC_H
#define ARGENTUM_NPC_H

#include "Mapa.h"
#include "GameObject.h"
#include "Movilidad.h"

class Movilidad;
class Mapa;

class Npc : public GameObject {
private:
    int lifePoints;
    Movilidad *mobility;
    //std::vector<Personaje*> &characters;
    //Criatura criatura
public:
    Npc(int lifePoints, Movilidad *movilidad, int x, int y, Mapa &mapa);
    Offset findClosestCharacterOffset();
    void move();
    ~Npc();
};



#endif //ARGENTUM_NPC_H

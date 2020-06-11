//
// Created by franco on 10/6/20.
//

#ifndef ARGENTUM_NPC_H
#define ARGENTUM_NPC_H


#include "GameObject.h"

class Npc : public GameObject {
private:
    int lifePoints;
    Movilidad *mobility;
    std::vector<Personaje*> &characters;
    //Criatura criatura

    std::vector<int> getRandomDir();
public:
    Npc(int vida,Movilidad* movilidad,float x,float y,Mapa& mapa);
    ~Npc();
    std::vector<int> findClosestCharacter();
    void move();
};



#endif //ARGENTUM_NPC_H

//
// Created by franco on 10/6/20.
//

#ifndef ARGENTUM_PLAYABLECHARACTER_H
#define ARGENTUM_PLAYABLECHARACTER_H

#include "GameObject.h"

class PlayableCharacter: public GameObject {
    //Clase clase
    //Raza raza
    int lifePoints;
    Movilidad *mobility;

    public:
        PlayableCharacter(int vida,Movilidad* movilidad,float x,float y,Mapa& mapa);
        void mover(Direccion* direccion);
};


#endif //ARGENTUM_PLAYABLECHARACTER_H

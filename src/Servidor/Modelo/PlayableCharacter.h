//
// Created by franco on 10/6/20.
//

#ifndef ARGENTUM_PLAYABLECHARACTER_H
#define ARGENTUM_PLAYABLECHARACTER_H

#include "GameObject.h"
#include "Movilidad.h"

class Movilidad;

class PlayableCharacter: public GameObject {
    //Clase clase
    //Raza raza
    int lifePoints;
    Movilidad *mobility;
    friend class PersonajeTest;
    public:
        PlayableCharacter(int lifePoints,Movilidad* movilidad,int x,int y,Mapa& mapa);
        void move(Offset& offset);
        virtual ~PlayableCharacter();
};


#endif //ARGENTUM_PLAYABLECHARACTER_H

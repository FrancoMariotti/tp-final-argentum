//
// Created by franco on 10/6/20.
//

#ifndef ARGENTUM_PLAYABLECHARACTER_H
#define ARGENTUM_PLAYABLECHARACTER_H

#include "GameObject.h"
#include "Mobility.h"

class Mobility;

class PlayableCharacter: public GameObject {
    //Clase clase
    //Raza raza
    int lifePoints;
    Mobility *mobility;
    friend class PersonajeTest;
    public:
        PlayableCharacter(int lifePoints, Mobility* mobility, int x, int y, Map& map);
        void move(Offset& offset);
        virtual ~PlayableCharacter();
};


#endif //ARGENTUM_PLAYABLECHARACTER_H

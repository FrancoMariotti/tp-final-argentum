#ifndef ARGENTUM_PLAYABLECHARACTER_H
#define ARGENTUM_PLAYABLECHARACTER_H

#include "Character.h"
#include "Mobility.h"

class Mobility;

class PlayableCharacter: public Character {
    //Clase clase
    //Raza raza
    int lifePoints;
    friend class PersonajeTest;
    public:
        PlayableCharacter(int lifePoints, int x, int y, Map& map);
        void move(Offset& offset);
        virtual ~PlayableCharacter();
};


#endif //ARGENTUM_PLAYABLECHARACTER_H

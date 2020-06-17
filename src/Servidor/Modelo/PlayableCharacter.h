#ifndef ARGENTUM_PLAYABLECHARACTER_H
#define ARGENTUM_PLAYABLECHARACTER_H

#include "Character.h"
#include "Mobility.h"

class Mobility;
class Game;

class PlayableCharacter: public Character {
    int lifePoints;
    int constitution;
    int agility;
    int strength;
    int intelligence;
    Game* game;
    friend class PersonajeTest;
public:
        PlayableCharacter(int lifePoints, int x, int y, Map& map,Game* game);
        void move(Offset& offset);
        ~PlayableCharacter() override;
};


#endif //ARGENTUM_PLAYABLECHARACTER_H

//
// Created by franco on 15/6/20.
//

#ifndef ARGENTUM_PLAYER_H
#define ARGENTUM_PLAYER_H

#include <string>
#include "PlayableCharacter.h"

class Player {
private:
    //std::string name;
    PlayableCharacter character;
public:
    Player(Map& map);
    ~Player();
    void move(Offset offset);
    //bool exists(std::string name);
};


#endif //ARGENTUM_PLAYER_H

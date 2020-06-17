//
// Created by franco on 15/6/20.
//

#ifndef ARGENTUM_PLAYER_H
#define ARGENTUM_PLAYER_H

#include <string>
#include "PlayableCharacter.h"

class Player {
    //std::string name;
    PlayableCharacter character;
public:
    Player(Map &map, Game* game);
    void move(Offset offset);
    ~Player();
    //bool exists(std::string name);
};


#endif //ARGENTUM_PLAYER_H

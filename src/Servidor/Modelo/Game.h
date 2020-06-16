//
// Created by franco on 15/6/20.
//

#ifndef ARGENTUM_GAME_H
#define ARGENTUM_GAME_H


#include <map>
#include "Map.h"
#include "Player.h"

class Game {
private:
    Map map;
    std::map<std::string, Player> players;
    //std::vector<Player*> players;
public:
    Game(std::string mapFile);
    ~Game();
    bool movePlayer(std::string playerName, Offset offset);
    void createPlayer(std::string name);
};


#endif //ARGENTUM_GAME_H

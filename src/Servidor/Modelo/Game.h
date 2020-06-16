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
    explicit Game(std::string mapFile);
    void movePlayer(std::string playerName, Offset offset);
    void createPlayer(std::string name);
    ~Game();
};


#endif //ARGENTUM_GAME_H

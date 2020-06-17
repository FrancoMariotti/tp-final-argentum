#ifndef ARGENTUM_GAME_H
#define ARGENTUM_GAME_H

#include <map>
#include "Map.h"
#include "Player.h"

class Update;

class Game {
private:
    Map map;
    std::map<std::string, Player> players;
    std::vector<Update> updates;
public:
    explicit Game(std::string mapFile);
    void movePlayer(const std::string& playerName, Offset offset);
    void createPlayer(const std::string& name);
    ~Game();

    void addUpdatePosition(int x, int y);
};


#endif //ARGENTUM_GAME_H

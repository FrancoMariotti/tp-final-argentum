#ifndef ARGENTUM_GAME_H
#define ARGENTUM_GAME_H

#include <map>
#include "Map.h"
#include "Factory.h"

class Update;
class PlayableCharacter;

class Game {
private:
    Map map;
    PlayableCharacterFactory factoryCharacters;
    //std::map<std::string, Player> players;
    std::map<std::string, PlayableCharacter> players;
    std::vector<Update> updates;
public:
    Game(std::string mapFile,std::string characterFile);
    void movePlayer(const std::string& playerName, Offset offset);
    void createPlayer(const std::string& name);
    ~Game();

    void addUpdatePosition(int x, int y);
};


#endif //ARGENTUM_GAME_H
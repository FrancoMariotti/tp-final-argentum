#ifndef ARGENTUM_GAME_H
#define ARGENTUM_GAME_H

#include <map>
#include "Map.h"
#include "Factory.h"
#include "Weapon.h"

class Update;
class PlayableCharacter;

class Game {
private:
    Map map;
    PlayableCharacterFactory factoryCharacters;
    NpcFactory npcFactory;
    //std::map<std::string, Player> players;
    std::map<std::string, PlayableCharacter> players;
    std::vector<Update> updates;
public:
    Game(std::string configFile);
    void movePlayer(const std::string& playerName, Offset offset);
    void createPlayer(const std::string& name, const std::string& charRace,
            const std::string& charClass);
    void createNpc(const std::string& specie);
    void equipWeapon(Weapon* weapon, std::string playerName);
    ~Game();

    void addUpdatePosition(int x, int y);
};


#endif //ARGENTUM_GAME_H

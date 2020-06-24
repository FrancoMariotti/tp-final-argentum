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
    Map* map;
    Json::Value obj;
    PlayableCharacterFactory factoryCharacters;
    NpcFactory npcFactory;
    std::vector<Update> updates;
public:
    Game(std::string gameConfigFilename);
    void createPlayer(const std::string& name, const std::string& charRace,
            const std::string& charClass);
    void createNpc(const std::string& specie);
    void equipWeapon(Weapon* weapon, std::string playerName);
    void movePlayer(const std::string& playerName, Offset& offset);
    void attackNpc(const std::string &playerName, Position &position);
    void attackPlayer(const std::string &playerName, const std::string &playerNameEnemy);
    void equipProtection(std::string playerName, Equippable element, int id);
    ~Game();
};


#endif //ARGENTUM_GAME_H

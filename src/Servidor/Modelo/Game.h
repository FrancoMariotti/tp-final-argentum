#ifndef ARGENTUM_GAME_H
#define ARGENTUM_GAME_H

#include <map>
#include <queue>
#include "Map.h"
#include "Factory.h"
#include "Weapon.h"
#include "Armour.h"

class Message;
class PlayableCharacter;
class ProxySocket;

class Game : public Observer {
private:
    std::string configFile;
    Map* map;
    PlayableCharacterFactory factoryCharacters;
    NpcFactory npcFactory;
    std::queue<Message*> updates;
public:
    Game(std::string gameConfigFilename);
    void createPlayer(const std::string& name, const std::string& charRace,
            const std::string& charClass);
    void createNpc(const std::string& specie);
    void equipWeapon(Weapon* weapon, std::string playerName);
    void movePlayer(const std::string& playerName, Offset& offset);
    void attackNpc(const std::string &playerName, Position &position);
    void attackPlayer(const std::string &playerName, const std::string &playerNameEnemy);
    void equipProtection(std::string playerName, Equippable element, Equipment equipment);
    void initializeMapLayers(ProxySocket& pxySkt);
    void movementUpdate(int x, int y) override;
    void sendUpdates(ProxySocket& pxySkt);
    ~Game();
};


#endif //ARGENTUM_GAME_H

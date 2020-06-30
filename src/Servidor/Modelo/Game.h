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
    std::queue<Message*> updates;
public:
    explicit Game(const std::string& gameConfigFilename);
    void createPlayer(const std::string& name, const std::string& charRace,
            const std::string& charClass);
    void initializeMap(ProxySocket& sck);
    void movePlayer(const std::string& playerName, Offset& offset);
    void attackNpc(const std::string &playerName, Position &position);
    void attackPlayer(const std::string &playerName, const std::string &playerNameEnemy);
    void storeInInventory(const std::string& playerName, Equippable* element);
    void equip(const std::string& playerName, int elementIndex);
    void unequip(const std::string& playerName, int elementIndex);
    void sendUpdates(ProxySocket& pxySkt);
    void movementUpdate(int x, int y) override;
    void statsUpdate(float health_percentage, float mana_percentage, float exp_percentage, int gold, int level) override;
    void itemsUpdate(std::vector<std::string> &vector) override ;
    void spawnNpcUpdate(std::vector<spawn_character_t> &npcs) override;
    void updateModel();
    void movementNpcUpdate(std::string idNpc, int x, int y) override;
    ~Game();
};


#endif //ARGENTUM_GAME_H

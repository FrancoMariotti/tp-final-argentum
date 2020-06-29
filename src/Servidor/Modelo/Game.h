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
    Game(const std::string& gameConfigFilename);
    void createPlayer(const std::string& name, const std::string& charRace,
            const std::string& charClass);
    void createNpc(const std::string& specie);
    void movePlayer(const std::string& playerName, Offset& offset);
    void attackNpc(const std::string &playerName, Position &position);
    void attackPlayer(const std::string &playerName, const std::string &playerNameEnemy);
    void storeInInventory(const std::string& playerName, Equippable* element);
    //void equipWeapon(Weapon* weapon, const std::string& playerName);
    void equip(const std::string& playerName, int elementIndex);
    void unequip(const std::string& playerName, int elementIndex);
    void initializeMapLayers(ProxySocket& pxySkt);
    void movementUpdate(int x, int y) override;
    void sendUpdates(ProxySocket& pxySkt);
    void statsUpdate(float health_percentage, float mana_percentage, float exp_percentage, int gold, int level) override;
    void drawUpdate(std::string id, std::vector<int> layer, int width, int height);
    ~Game();

    void updateCharacterItems(std::vector<std::string> &vector);
};


#endif //ARGENTUM_GAME_H

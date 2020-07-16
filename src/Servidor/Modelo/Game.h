#ifndef ARGENTUM_GAME_H
#define ARGENTUM_GAME_H

#include <map>
#include <queue>
#include "Map.h"
#include "Factory.h"
#include "Weapon.h"
#include "Armour.h"
#include "CommandExecutor.h"
#include <memory>

class Message;
class PlayableCharacter;
class ProxySocket;

class Game : public Observer {
private:
    std::string configFile;
    MapFactory mapFactory;
    Map* map;
    CommandExecutor commandExecutor;
    PlayableCharacterFactory factoryCharacters;
    NpcFactory npcFactory;
    std::queue<std::tuple<std::string,Message*>> directedUpdates;
    std::queue<Message*> broadcastUpdates;
public:
    explicit Game(const std::string& gameConfigFilename);
    void createPlayer(const std::string& name, const std::string& charRace,
            const std::string& charClass);
    void movePlayer(const std::string& playerName, Offset& offset);
    void attack(const std::string &playerName, Position &position);
    //void storeInInventory(const std::string& playerName, Equippable* element);
    void equip(const std::string& playerName, int elementIndex);
    void unequip(const std::string& playerName, int elementIndex);
    void notifymovementUpdate(std::string id,int x, int y) override;
    void notifyStatsUpdate(std::string& username,float health_percentage, float mana_percentage, float exp_percentage, int gold, int level) override;
    void notifyEquipmentUpdate(std::string& username,std::string weaponName, std::string armourName, std::string shieldName, std::string helmetName) override;
    void notifyItemsUpdate(std::string& username,std::vector<std::string> &vector) override;
    void notifySpawnNpcUpdate(std::vector<location_t> &npcs) override;
    void notifySpawnPcUpdate(std::vector<spawn_playable_character_t> pcSpawns) override;
    void notifyDropSpawnNUpdate(std::vector<location_t> dropSpawns) override ;
    void notifyCityCharactersSpawn(std::vector<location_t> &spawns) override;
    void notifyMovementNpcUpdate(std::string idNpc, int x, int y) override;
    void updateModel(float looptime);
    void createNpc(const std::string &specie);
    void initialize();
    std::queue<Message *> initializeWorld();
    void executeCommand(std::unique_ptr<Message>& msg);
    void notifyConsoleOutputUpdate(std::string& username,std::vector<std::string> messages) override;
    bool broadcastUpdateAvailable();
    bool directedUpdateAvailable();
    Message *nextBroadCastUpdate();
    std::tuple<std::string,Message*> nextDirectedUpdate();
    ~Game();
};


#endif //ARGENTUM_GAME_H

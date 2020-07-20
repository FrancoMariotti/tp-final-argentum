//
// Created by franco on 19/7/20.
//

#ifndef ARGENTUM_PERSISTANCEMANAGER_H
#define ARGENTUM_PERSISTANCEMANAGER_H

#include <map>
#include <vector>

#define CHARACTER_INFO_INTS_AMOUNT 45

class Configuration;
class PlayableCharacter;
class Observer;
class Map;
class PlayableCharacterFactory;

typedef struct character_info {
   int lifePoints;
   int level;
   int constitution;
   int agility;
   int strength;
   int intelligence;
   int raceLifeFactor;
   int classLifeFactor;
   int raceManaFactor;
   int classManaFactor;
   int recoveryFactor;
   int meditationRecoveryFactor;
   int x;
   int y;
   int mana;
   int gold;
   int xp;
   std::vector<int> inventoryItems;
   int activeWeapon;
   std::vector<int> protections;
   int lifeState;
   int inCity;
   int goldInBank;
   std::vector<int> itemsInBank;
   int race;
} character_info_t;

typedef struct login_info {
    std::string password;
    int index;
} login_info_t;

class PersistanceManager {
    std::string playersInfoMapFile;
    std::string playersInfoFile;
    std::map<std::string, login_info_t> playersInfoMap;
    int playersAmount;
    Configuration& config;
    void addPlayerInfoToFile(character_info_t playerInfo, int index);
    character_info_t getPlayerInfoFromFile(int index);
public:
    PersistanceManager(std::string playersInfoMapFile, std::string  playersInfoFile);
    void persistPlayerData(PlayableCharacter *pCharacter);
    bool login(const std::string &playerName, std::string &password, Map* map,
            Observer* observer, PlayableCharacterFactory& pcFactory);
    void signup(const std::string &username, const std::string &password);

    bool existsUser(const std::string &username);
};


#endif //ARGENTUM_PERSISTANCEMANAGER_H

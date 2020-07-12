#ifndef ARGENTUM_MAPA_H
#define ARGENTUM_MAPA_H

#include <Proxy/src/common_message.h>
#include "map"
#include "vector"
#include "Position.h"
#include "Obstacle.h"
#include "Weapon.h"
#include "Equippable.h"
#include "Observer.h"
#include "Factory.h"
#include "Drop.h"
#include "City.h"
#include "Banker.h"
#include <queue>
#include <memory>

class Message;
class Character;
class Npc;
class PlayableCharacter;
class Weapon;
class ProxySocket;


class Map {
    int width;
    int height;
    float lastNpcUpdate;
    Banker banker;
    Merchant merchant;
    Priest priest;
    std::vector<spawn_character_t> cityCharactersSpawns;
    //std::vector<spawn_character_t> npcSpawns;
    std::vector<spawn_character_t> dropsSpawns;
    std::map<std::string,PlayableCharacter*> characters;
    std::map<std::string,Npc*> npcs;
    std::vector<Obstacle> obstacles;
    std::vector<City> cities;
    std::vector<Drop> drops;
    public:
        Map(int width,int height);
        void add(const std::string& playerName,PlayableCharacter* character);
        void add(std::string idNpc, Npc *npc);
        void add(const Obstacle& obstacle);
        void add(City city);
        bool isOccupied(Position pos);
        bool outOfBounds(Position position) const;
        void move(Position& from,Position& to);
        Character* findClosestCharacter(const Position& pos, int range);
        PlayableCharacter *getPlayer(const std::string &basicString);
        void sendLayers(ProxySocket& sck,const std::string& configFile) const;
        //void registerNpcSpawn(Observer * observer,spawn_character_t spawn);
        void moveNpcs(float looptime);
        void updateAllPlayers(float looptime, Observer* observer);
        Position asignRandomPosition();
        Position asignRandomPosInAnyCity();
        void addDrop(Drop drop);
        void removePlayableCharacter(const std::string &playerName);
        void removeNpc(const std::string& idNpc, Observer* observer);
        bool posInCity(Position position);
        Character *findCharacterAtPosition(Position &position);
        void registerCityCharactersSpawns(std::vector<spawn_character_t> &spawns);
        //void spawnCityCharacters(Observer *observer);
        Position getRandomPosAtClosestPriestCity(PlayableCharacter *player);
        Banker* getBankerAtPosition(const Position& position);
        Merchant* getMerchantAtPosition(Position position);
        Priest* getPriestAtPosition(const Position& position);
        void reviveIn(PlayableCharacter *player, Position position);
        void add(Banker pBanker);
        void add(Merchant pMerchant);
        void add(Priest priest);
        bool hasDropInPos(Position position);
        void updateDropSpawns(Observer *observer);
        Drop takeDropFromPos(Position position);
        std::queue<Message *> initializeClientMap(const std::string &configFile) const;
        void regenerateNpcs(float loopTimeInSeconds, NpcFactory& npcFactory, Observer* observer);
        void addLayersTo(std::string configFile, std::queue<Message*>& initializeMessages);
        void initializeDropSpawns(std::queue<Message*>& initializeMessages);
        void initializeNpcsSpawns(std::queue<Message*>& initializeMessages);
        void updateNpcsSpawns(Observer* observer);
        void updatePcSpawns(Observer* observer);
        void initializePlayersSpawns(std::queue<Message*>& initializeMessages);
        ~Map();


};

#endif //ARGENTUM_MAPA_H

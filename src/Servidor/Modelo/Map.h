#ifndef ARGENTUM_MAPA_H
#define ARGENTUM_MAPA_H

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

class Character;
class Npc;
class PlayableCharacter;
class Weapon;
class ProxySocket;


class Map {
    int width;
    int height;
    std::vector<spawn_character_t> cityCharactersSpawns;
    std::vector<spawn_character_t> npcSpawns;
    std::map<std::string,PlayableCharacter*> characters;
    std::map<std::string,Npc*> npcs;
    std::vector<Obstacle> obstacles;
    std::vector<City> cities;
    public:
        Map();
        Map(const std::string& configFile, int width, int height);
        void add(const std::string& playerName,PlayableCharacter* character);
        void add(std::string idNpc, Npc *npc);
        void add(const Obstacle& obstacle);
        void add(City city);
        bool isOccupied(Position pos);
        void move(Position& from,Position& to);
        Character* findClosestCharacter(const Position& pos, int range);
        PlayableCharacter *getPlayer(const std::string &basicString);
        void sendLayers(ProxySocket& sck,const std::string& configFile) const;
        void registerNpcSpawn(Observer * observer,spawn_character_t spawn);
        void moveNpcs(float looptime);
        void updateAllPlayers(float looptime);
        Position asignRandomPosition();
        Position asignRandomPosInAnyCity();
        void addDrop(Drop drop);
        void removePlayableCharacter(const std::string &playerName);
        void removeNpc(const std::string& idNpc, Observer* observer);
        bool posInCity(Position position);
        Character *findCharacterAtPosition(Position &position);
        void depositInBank(PlayableCharacter *player, const Position& position,const std::string& element);
        void registerCityCharactersSpawns(std::vector<spawn_character_t> &spawns);
        void depositInBank(PlayableCharacter *player, const Position& position, int gold_amount);
        void spawnCityCharacters(Observer *observer);
        void extractFromBank(PlayableCharacter *player, const Position& position, int goldAmount);
        void extractFromBank(PlayableCharacter *player, const Position& position, const std::string& element);
        void searchPriestToRevive(PlayableCharacter *character, Position position);
        void reviveNextToClosestPriest(PlayableCharacter *character);
        void searchPriestToHeal(PlayableCharacter *character, Position position);
        void buyItem(PlayableCharacter *player, const Position& position, const std::string& item);
        ~Map();

};

#endif //ARGENTUM_MAPA_H

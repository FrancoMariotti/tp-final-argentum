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

class Character;
class Npc;
class PlayableCharacter;
class Weapon;
class ProxySocket;

class Map {
    int width;
    int height;
    std::vector<spawn_character_t> spawns;
    std::map<std::string,PlayableCharacter*> characters;
    std::map<std::string,Npc*> npcs;
    std::vector<Obstacle> obstacles;
    std::vector<City> cities;
    public:
        Map();
        Map(int width, int height);
        void addPlayableCharacter(const std::string& playerName,PlayableCharacter* character);
        void addNpc(std::string idNpc, Npc *npc);
        void addObstacle(const Obstacle& obstacle);
        void addCity(City city);
        bool isOccupied(Position pos);
        void move(Position& from,Position& to);
        Character* findNpcAtPosition(Position &position);
        Character* findClosestCharacter(const Position& pos, int range);
        PlayableCharacter *getPlayer(const std::string &basicString);
        void sendLayers(ProxySocket& sck,const std::string& configFile) const;
        void registerNpcSpawn(Observer * observer,spawn_character_t spawn);
        void moveNpcs(float looptime);
        void updateAllPlayers(float looptime);
        Position asignRandomPosition();
        void addDrop(Drop drop);
        void removePlayableCharacter(const std::string &playerName);
        void removeNpc(const std::string& idNpc);
        ~Map();

    bool posInCity(Position position);
};

#endif //ARGENTUM_MAPA_H

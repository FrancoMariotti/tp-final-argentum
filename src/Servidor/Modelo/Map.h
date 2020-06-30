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

class Character;
class Npc;
class PlayableCharacter;
class Weapon;
class ProxySocket;

class Map {
    int width;
    int height;
    NpcFactory npcFactory;
    std::vector<spawn_character_t> spawns;
    std::map<std::string,PlayableCharacter*> characters;
    std::vector<Npc*> npcs;
    std::vector<Obstacle*> obstacles;
    public:
        Map();
        Map(std::string configFile, int width, int height);
        void addPlayableCharacter(const std::string& playerName,PlayableCharacter* character);
        void addNpc(Npc* npc);
        void addObstacle(Obstacle* obstacle);
        bool isOccupied(Position pos);
        void move(Position& from,Position& to);
        Character* findNpcAtPosition(Position &position);
        Character* findClosestCharacter(const Position& pos, int range);
        PlayableCharacter *getPlayer(const std::string &basicString);
        void sendLayers(ProxySocket& sck,std::string configFile) const;
        void registerNpcSpawn(spawn_character_t spawn);
        void update(Observer *observer);
        void moveNpcs(float looptime);
        Position asignRandomPosition();
        ~Map();
};

#endif //ARGENTUM_MAPA_H

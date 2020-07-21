#ifndef ARGENTUM_MAPA_H
#define ARGENTUM_MAPA_H

#include <Common/Messages/Message.h>
#include "map"
#include "vector"
#include "Position.h"
#include "Obstacle.h"
#include "Server/Model/Equippables/Weapon.h"
#include "Server/Model/Equippables/Equippable.h"
#include "Server/Model/Observer.h"
#include "Server/Model/Factory.h"
#include "Server/Model/Dropppables/Drop.h"
#include "City.h"
#include "Server/Model/Character/Banker.h"
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
    float lastPersistance;
    Banker banker;
    Merchant merchant;
    Priest priest;
    std::vector<location_t> cityCharactersSpawns;
    std::vector<location_t> dropsSpawns;
    std::map<std::string,PlayableCharacter*> characters;
    std::map<std::string,Npc*> npcs;
    std::vector<Obstacle> obstacles;
    std::vector<City> cities;
    std::vector<Drop> drops;
    Configuration& config;
    public:
        Map(int width,int height);
        void add(const std::string& playerName,PlayableCharacter* character);
        void add(std::string idNpc, Npc *npc);
        void add(const Obstacle& obstacle);
        void add(City city);
        void add(Banker pBanker);
        void add(Merchant pMerchant);
        void add(Priest priest);
        //Devuelve true si la posicion recibida por parametro esta ocupada
        //y false en caso contrario.
        bool isOccupied(Position pos);
        //Devuelve true si la posicion recibida por parametro esta fuera de los
        // limites del mapa y false en caso contrario.
        bool outOfBounds(Position position) const;
        //Recibe dos posicion y chequea si la posicion param:to esta ocupada.
        //Si la posicion param:to esta libre entonces iguala param:from y param:to.
        void move(Position& from,Position& to);
        //Busca al Character mas cercano a la posicion param:pos en el rango param:range.
        Character* findClosestCharacter(const Position& pos, int range);
        PlayableCharacter *getPlayer(const std::string &basicString);
        //Recibe el tiempo de GameLoop y mueve a todos los npcs luego de transcurrido
        // una cantidad determinada de gameloops
        void moveNpcs(float looptime);
        //udpatea todos los parametros dependientes del tiempo del player.
        void updateAllPlayers(float looptime, Observer* observer);
        Position asignRandomPosition();
        Position asignRandomPosInAnyCity();
        void addDrop(Drop drop);
        void removePlayableCharacter(const std::string &playerName);
        void removeNpc(const std::string& idNpc, Observer* observer);
        //devuelve true si la posicion en recibida por parametro es una posicion en alguna
        // de las ciudades false en caso contrario.
        bool posInCity(Position position);
        Character *findCharacterAtPosition(Position &position);
        void registerCityCharactersSpawns(std::vector<location_t> &spawns);
        Position getRandomPosAtClosestPriestCity(PlayableCharacter *player);
        Banker* getBankerAtPosition(const Position& position);
        Merchant* getMerchantAtPosition(Position position);
        Priest* getPriestAtPosition(const Position& position);
        void reviveIn(PlayableCharacter *player, Position position);
        bool hasDropInPos(Position position);
        void updateDropSpawns(Observer *observer);
        //Recibe una posicion y devuelve el drop ubicado en dicha posicion.
        //En caso de que no haya un drop en la posicion se devuelve un drop vacio.
        Drop takeDropFromPos(Position position);
        void regenerateNpcs(float loopTimeInSeconds, NpcFactory& npcFactory, Observer* observer);
        void addLayersTo(std::string configFile, std::queue<Message*>& initializeMessages);
        //Recibe una queue de mensajes iniciales y agrega un mensaje a la queue con todos los drop
        // que se encuentran en el mapa
        void initializeDropSpawns(std::queue<Message*>& initializeMessages);
        //Recibe una queue de mensajes iniciales y agrega un mensaje a la queue con todos los npcs
        // que se encuentran en el mapa
        void initializeNpcsSpawns(std::queue<Message*>& initializeMessages);
        void updateNpcsSpawns(Observer* observer);
        void updatePlayersSpawns(std::queue<Message*>& initializeMessages);
        void persistPlayersData(PersistanceManager& pManager, float loopTImeInSeconds);
        void disconnectPlayer(const std::string& username, PersistanceManager& pManager);
        Drop getDropAtPos(Position& position);
        ~Map();

};

#endif //ARGENTUM_MAPA_H

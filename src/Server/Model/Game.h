#ifndef ARGENTUM_GAME_H
#define ARGENTUM_GAME_H

#include <map>
#include <queue>
#include "Server/Model/Map/Map.h"
#include "Factory.h"
#include "Server/Model/Equippables/Weapon.h"
#include "Server/Model/Character/Armour.h"
#include "Server/Model/Commands/CommandExecutor.h"
#include <memory>

class Message;
class PlayableCharacter;
class ProxySocket;

class Game : public Observer {
private:
    std::string configFile;
    ItemFactory itemFactory;
    MapFactory mapFactory;
    Map* map;
    CommandExecutor commandExecutor;
    PlayableCharacterFactory factoryCharacters;
    NpcFactory npcFactory;
    std::queue<std::tuple<std::string,Message*>> directedUpdates;
    std::queue<Message*> broadcastUpdates;
    PersistanceManager persistanceManager;
public:
    explicit Game(const std::string& gameConfigFilename, const std::string& playersInfoMapFile,
            const std::string& playersInfoFile);
    //Crea un PlayableCharacter con el nombre, raza y clase recibido por parametro.
    void createPlayer(const std::string& name, const std::string& charRace,
            const std::string& charClass);
    //Notifica al PlayableCharacter con nombre de usuario(param:playerName)
    //que debe moverse un determinado offset.
    void movePlayer(const std::string& playerName, Offset& offset);
    //Notifica al PlayableCharacter con nombre de usuario(param:playerName)
    //que debe atacar al a un otro player ubicado en la posicion
    //recibida por parametro.
    void attack(const std::string &playerName, Position &position);
    //Notifica al PlayableCharacter con nombre de usuario(param:playerName)
    //que debe equiparse un equipable ubicado en el indice del inventario
    //recibido por parametro.
    void equip(const std::string& playerName, int elementIndex);
    //Notifica al PlayableCharacter con nombre de usuario(param:playerName)
    //que debe des equiparse un equipable ubicado en el indice del inventario
    //recibido por parametro.
    void unequip(const std::string& playerName, int elementIndex);
    void notifymovementUpdate(std::string id,int x, int y) override;
    void notifyStatsUpdate(std::string& username,float health_percentage, float mana_percentage,
                                                float exp_percentage, int gold, int level) override;
    void notifyEquipmentUpdate(std::string& username,std::string weaponName, std::string armourName,
                                                std::string shieldName, std::string helmetName) override;
    void notifyItemsUpdate(std::string& username,std::vector<std::string> &vector) override;
    void notifySpawnNpcUpdate(std::vector<location_t> &npcs) override;
    void notifyDropSpawnNUpdate(std::vector<location_t> dropSpawns) override ;
    void notifyCityCharactersSpawn(std::vector<location_t> &spawns) override;
    void notifyMovementNpcUpdate(std::string idNpc, int x, int y) override;
    void notifyConsoleOutputUpdate(std::string& username,std::vector<std::string> messages) override;
    //Recibe el tiempo de duracion del GameLoop y updatea todos los elementos
    // del juego que varian con el tiempo (movimiento de los npcs,regeneracion de los
    // npcs,recuperacion de mana por tiempo del playable character...).
    void updateModel(float looptime);
    //Crea un Npc de la especie recibida por parametro.
    void createNpc(const std::string &specie);
    //Se crean todos los elementos necesarios para inicializacion del juego.
    void initialize();
    //Devuelve una queue con los mensajes necesarios para que el cliente pueda
    //dibujar el mundo cuando este se conecta.
    std::queue<Message *> initializeWorld();
    //Recibe un mensaje y ejecuta el comando recibido con la informacion que
    // contiene el mensaje.
    void executeCommand(std::unique_ptr<Message>& msg);
    bool broadcastUpdateAvailable();
    bool directedUpdateAvailable();
    //Devuelve el mensaje al frente de la queue de updates de broadcast.
    Message *nextBroadCastUpdate();
    //Devuelve la tupla al frente de la queue de updates dirigidos.
    std::tuple<std::string,Message*> nextDirectedUpdate();
    //Persiste la informacion de todos los jugadores conectados cuando transcurre
    //determinado tiempo.
    void persistPlayersData(float loopTimeInSeconds);
    bool login(const std::string &username, std::string &password);
    bool existsUser(const std::string &username);
    void signup(const std::string &username, const std::string &password);
    //Elimina al player desconectado del mapa a partir del username recibido por
    //parametro.
    std::queue<Message*> disconnectPlayer(const std::string& username);
    ~Game();
};


#endif //ARGENTUM_GAME_H

#ifndef ARGENTUM_OBSERVER_H
#define ARGENTUM_OBSERVER_H


typedef struct spawn_character spawn_character_t;
typedef struct spawn_playable_character spawn_playable_character_t;
class Observer {
public:
    virtual void notifymovementUpdate(int x, int y) = 0;

    virtual void
    notifyStatsUpdate(float health_percentage, float mana_percentage, float exp_percentage, int gold, int level) = 0;

    virtual void notifyItemsUpdate(std::vector<std::string> &vector) = 0;

    virtual void notifySpawnNpcUpdate(std::vector<spawn_character_t> &npcs) = 0;

    virtual void notifyMovementNpcUpdate(std::string idNpc, int x, int y) = 0;

    virtual void
    notifyEquipmentUpdate(std::string weaponName, std::string armourName,
            std::string shieldName, std::string helmetName) = 0;

    virtual void
    notifyCityCharactersSpawn(std::vector<spawn_character_t> &spawns) = 0;

    virtual void notifyDropSpawnNUpdate(std::vector<spawn_character_t> dropSpawns) = 0;
    virtual void notifySpawnPcUpdate(std::vector<spawn_playable_character_t> pcSpawns) = 0;
    virtual void notifyConsoleOutputUpdate(std::vector<std::string> messages) = 0;

};

#endif //ARGENTUM_OBSERVER_H

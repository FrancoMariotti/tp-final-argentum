#ifndef ARGENTUM_OBSERVER_H
#define ARGENTUM_OBSERVER_H

typedef struct spawn_character spawn_character_t;
class Observer {
public:
    virtual void movementUpdate(int x, int y) = 0;

    virtual void
    statsUpdate(float health_percentage, float mana_percentage, float exp_percentage, int gold, int level) = 0;

    virtual void itemsUpdate(std::vector<std::string> &vector) = 0;

    virtual void spawnNpcUpdate(std::vector<spawn_character_t> &npcs) = 0;
};

#endif //ARGENTUM_OBSERVER_H

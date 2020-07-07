//
// Created by agustin on 26/6/20.
//

#ifndef ARGENTUM_COMMON_MESSAGE_STRUCTS_H
#define ARGENTUM_COMMON_MESSAGE_STRUCTS_H

#include <string>

typedef struct t_stats{
    float health_percentage;
    float mana_percentage;
    float exp_percentage;
    int gold;
    int level;
}t_stats;

typedef struct equipment {
    std::string weaponName;
    std::string armourName;
    std::string shieldName;
    std::string helmetName;
} equipment_t;

typedef struct spawn_character {
    int x;
    int y;
    std::string id;
} spawn_character_t;


typedef struct npc_movement {
    int x;
    int y;
    std::string id;
} npc_movement_t;

typedef struct player_attack {
    std::string username;
    int enemy_x;
    int enemy_y;
} t_player_attack;

typedef struct spawn_playable_character {
    int x;
    int y;
    std::string username;
    std::string race;
    std::string weaponName;
    std::string armourName;
    std::string shieldName;
    std::string helmetName;
} spawn_playable_character_t;

#endif //ARGENTUM_COMMON_MESSAGE_STRUCTS_H

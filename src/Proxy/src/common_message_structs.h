//
// Created by agustin on 26/6/20.
//
#ifndef ARGENTUM_COMMON_MESSAGE_STRUCTS_H
#define ARGENTUM_COMMON_MESSAGE_STRUCTS_H

#include <msgpack.hpp>

typedef struct t_stats{
    float health_percentage;
    float mana_percentage;
    float exp_percentage;
    int gold;
    int level;
    MSGPACK_DEFINE(health_percentage,
                   mana_percentage,
                   exp_percentage,
                   gold,
                   level)
}t_stats;

typedef struct connect {
    std::string username;
    std::string charRace;
    std::string charClass;
    MSGPACK_DEFINE(username,
                   charRace,
                   charClass)
}connect_t;

typedef struct equipment {
    std::string weaponName;
    std::string armourName;
    std::string shieldName;
    std::string helmetName;
    MSGPACK_DEFINE(weaponName,
                   armourName,
                   shieldName,
                   helmetName)
} equipment_t;

typedef struct spawn_character {
    int x;
    int y;
    std::string id;
    MSGPACK_DEFINE(x,
                   y,
                   id)
} spawn_character_t;


typedef struct npc_movement {
    int x;
    int y;
    std::string id;
    MSGPACK_DEFINE(x,
                   y,
                   id)
} npc_movement_t;

typedef struct player_attack {
    std::string username;
    int enemy_x;
    int enemy_y;
    MSGPACK_DEFINE(username,
                   enemy_x,
                   enemy_y)
} t_player_attack;


#endif //ARGENTUM_COMMON_MESSAGE_STRUCTS_H

#ifndef ARGENTUM_MESSAGE_STRUCTS_H
#define ARGENTUM_MESSAGE_STRUCTS_H

#include <msgpack.hpp>
#include <string>

typedef struct stats {
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

typedef struct equipment {
    std::string username;
    std::string weaponName;
    std::string armourName;
    std::string shieldName;
    std::string helmetName;
    MSGPACK_DEFINE( username,
                    weaponName,
                    armourName,
                    shieldName,
                    helmetName)
} equipment_t;

typedef struct location {
    int x;
    int y;
    std::string id;
    MSGPACK_DEFINE(x,
                   y,
                   id)
} location_t;

typedef struct spawn_playable_character {
    int x;
    int y;
    std::string username;
    std::string race;
    std::string weaponName;
    std::string armourName;
    std::string shieldName;
    std::string helmetName;
    MSGPACK_DEFINE(x,
                y,
                username,
                race,
                weaponName,
                armourName,
                shieldName,
                helmetName)
} spawn_playable_character_t;

typedef struct create_player {
    std::string username;
    std::string password;
    std::string race;
    std::string charClass;
    MSGPACK_DEFINE(username,
                   password,
                   race,
                   charClass)
} create_player_t;

typedef struct command {
    std::string username;
    std::string input;
    int x;
    int y;
    MSGPACK_DEFINE(username,
                   input,
                   x,
                   y)
} command_t;

typedef struct client_login {
    std::string username;
    std::string password;
    int id;
    MSGPACK_DEFINE(username,
                   password,
                   id)
} t_client_login;

#endif //ARGENTUM_MESSAGE_STRUCTS_H

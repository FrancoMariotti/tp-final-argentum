//
// Created by agustin on 26/6/20.
//

#ifndef ARGENTUM_COMMON_MESSAGE_STRUCTS_H
#define ARGENTUM_COMMON_MESSAGE_STRUCTS_H

typedef struct t_stats{
    float health_percentage;
    float mana_percentage;
    float exp_percentage;
    int gold;
    int level;
}t_stats;

typedef struct spawn_character {
    int x;
    int y;
    std::string id;
} spawn_character_t;

#endif //ARGENTUM_COMMON_MESSAGE_STRUCTS_H

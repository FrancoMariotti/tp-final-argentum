//
// Created by agustin on 26/6/20.
//

#include "client_sdl_stats.h"
#include "common_message_structs.h"

SdlStats::SdlStats(const int screen_width, const int screen_height, const SdlWindow &window, TTF_Font *font) :
        xpBar(screen_width - 200,140,0x33,0xAA,0x33,0xFF,window),
        level(screen_width - 200, 120, window, font, "Level: "),
        healthBar(screen_width - 200,screen_height - 250,0xFF,0x00,0x00,0xFF,window),
        manaBar(screen_width - 200,screen_height - 200,0x10,0x00,0x88,0xFF,window),
        gold(screen_width - 200, screen_height - 150, window, font, "Gold: ")
        {}

void SdlStats::update(t_stats stats){
    healthBar.update(stats.health_percentage);
    manaBar.update(stats.mana_percentage);
    xpBar.update(stats.exp_percentage);
    std::string s_gold = std::to_string(stats.gold);
    gold.update(s_gold);
    std::string s_level = std::to_string(stats.level);
    level.update(s_level);
}

void SdlStats::render(){
    healthBar.render();
    manaBar.render();
    xpBar.render();
    gold.render();
    level.render();
}
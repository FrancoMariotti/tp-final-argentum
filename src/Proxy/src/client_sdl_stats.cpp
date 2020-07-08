//
// Created by agustin on 26/6/20.
//

#include <iostream>
#include "client_sdl_stats.h"
#include "common_message_structs.h"
#include "client_sdl_window.h"

SdlStats::SdlStats(const SdlWindow &window, TTF_Font *font) :
        levelLabel(window.getWidth() - 200, 120, window, font, "Level: "),
        xpBar(window.getWidth() - 200,140,0x33,0xAA,0x33,0xFF,window),
        healthBar(window.getWidth() - 200,window.getHeight() - 250,0xFF,0x00,0x00,0xFF,window),
        manaBar(window.getWidth() - 200,window.getHeight() - 200,0x10,0x00,0x88,0xFF,window),
        goldLabel(window.getWidth() - 200, window.getHeight() - 150, window, font, "Gold: "),
        manaLabel(window.getWidth() - 200, window.getHeight() - 220, window, font, "Mana: "),
        lifeLabel(window.getWidth() - 200, window.getHeight() - 270, window, font, "Life: ")
        {}

void SdlStats::update(t_stats stats){
    healthBar.update(stats.health_percentage);
    manaBar.update(stats.mana_percentage);
    xpBar.update(stats.exp_percentage);
    std::string s_gold = std::to_string(stats.gold);
    goldLabel.update(s_gold);
    std::string s_level = std::to_string(stats.level);
    levelLabel.update(s_level);
    //Agregamos esto para mostrar el cartel de vida y mana
    int manaPercentaje = stats.mana_percentage * 100;
    std::string s_mana = std::to_string(manaPercentaje);
    manaLabel.update(s_mana + "%");
    int healthPercentaje = stats.health_percentage * 100;
    std::string s_health = std::to_string(healthPercentaje);
    lifeLabel.update(s_health + "%");
}

void SdlStats::render(){
    healthBar.render();
    manaBar.render();
    xpBar.render();
    goldLabel.render();
    levelLabel.render();
    //Agregamos esto para mostrar el cartel de vida y mana
    manaLabel.render();
    lifeLabel.render();
}
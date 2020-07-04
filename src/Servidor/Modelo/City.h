//
// Created by franco on 2/7/20.
//

#ifndef ARGENTUM_CITY_H
#define ARGENTUM_CITY_H

#include "Obstacle.h"
#include "Priest.h"
#include "Merchant.h"
#include "Banker.h"

class City : public Obstacle {
    Priest priest;
    Merchant merchant;
    Banker banker;
public:
    City(int x, int y, int height, int width,std::string configFile,
         const Json::Value& priestItems,const Position& priestPos, const Json::Value& merchantItems,
         const Position& merchantPos, const Position& bankerPos);
    City(City &&city) noexcept ;
    bool isOcupied(const Position& pos);
    void depositInBank(const Position& pos, PlayableCharacter *player,std::string item);
    void depositInBank(const Position& pos, PlayableCharacter *player, int gold_amount);
    void buyItem(const Position& pos, PlayableCharacter *player, const std::string& item);
    void searchPriestToRevive(PlayableCharacter* character, Position pos);
    void searchPriestToHeal(PlayableCharacter* character, Position pos);
    void extractFromBank(const Position& pos, PlayableCharacter *player, const std::string& item);
    void extractFromBank(const Position& pos, PlayableCharacter *player, int goldAmount);
    int distanceToPriest(PlayableCharacter* character);
    void revivePlayerHere(PlayableCharacter *character, Map* map);
    Position getRandomPos(Map *map);

};


#endif //ARGENTUM_CITY_H

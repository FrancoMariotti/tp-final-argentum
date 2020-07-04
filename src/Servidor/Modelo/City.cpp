#include <utility>
#include "City.h"
#include "PlayableCharacter.h"

City::City(int x, int y, int height, int width,
           const Json::Value& priestItems,const Position& priestPos, const Json::Value& merchantItems,
           const Position& merchantPos, const Position& bankerPos): Obstacle(x, y, height, width),
           priest(priestItems,priestPos),merchant(merchantItems,merchantPos), banker(bankerPos){}

City::City(City &&city) noexcept:Obstacle(city),priest(std::move(city.priest)),
                merchant(std::move(city.merchant)),banker(city.banker)  {}

bool City::isOcupied(const Position& pos) {
    return priest.pos == pos || banker.pos == pos || merchant.pos == pos;
}

void City::depositInBank(const Position& pos, PlayableCharacter *player, std::string item) {
    if(banker.pos == pos) player->deposit(std::move(item),&banker);
}

void City::depositInBank(const Position& pos, PlayableCharacter *player, int gold_amount) {
    if(banker.pos == pos) player->deposit(gold_amount,&banker);
}

void City::extractFromBank(const Position &pos, PlayableCharacter *player, std::string item) {
    if(banker.pos == pos) player->extract(item,&banker);
}

void City::extractFromBank(const Position &pos, PlayableCharacter *player, int goldAmount) {
    if(banker.pos == pos) player->extract(goldAmount,&banker);
}

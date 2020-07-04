#include <utility>
#include <Servidor/Common/Utils.h>
#include "City.h"
#include "PlayableCharacter.h"

City::City(int x, int y, int height, int width,std::string configFile,
           const Json::Value& priestItems,const Position& priestPos, const Json::Value& merchantItems,
           const Position& merchantPos, const Position& bankerPos): Obstacle(x, y, height, width),
           priest(configFile,priestItems,priestPos),merchant(configFile,merchantItems,merchantPos), banker(bankerPos){}

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

void City::searchPriestToRevive(PlayableCharacter* character, Position pos) {
    if(priest.pos == pos) priest.revive(character);
}

void City::searchPriestToHeal(PlayableCharacter *character, Position pos) {
    if(priest.pos == pos) priest.restoreManaAndLife(character);
}

int City::distanceToPriest(PlayableCharacter *character) {
    return character->distanceTo(priest.pos);
}

void City::extractFromBank(const Position &pos, PlayableCharacter *player, const std::string& item) {
    if(banker.pos == pos) player->extract(item,&banker);
}

void City::extractFromBank(const Position &pos, PlayableCharacter *player, int goldAmount) {
    if(banker.pos == pos) player->extract(goldAmount,&banker);
}

void City::buyItem(const Position &pos, PlayableCharacter *player, const std::string& item) {
    if(merchant.pos == pos) player->buyFrom(item,&merchant);
    if(priest.pos == pos) player->buyFrom(item,&priest);
}

Position City::getRandomPos(Map *map) {
    int x, y;
    x = Utils::random_int_number(position.getX(), position.getX() + height - 1);
    y = Utils::random_int_number(position.getY(), position.getY() + width - 1);
    while (map->isOccupied(Position(x, y))) {
        x = Utils::random_int_number(position.getX(), position.getX() + height - 1);
        y = Utils::random_int_number(position.getY(), position.getY() + width - 1);
    }
    return Position(x, y);
}

void City::revivePlayerHere(PlayableCharacter *character, Map* map) {
    priest.reviveIn(character, getRandomPos(map));
}


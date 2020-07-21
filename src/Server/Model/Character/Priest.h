#ifndef ARGENTUM_PRIEST_H
#define ARGENTUM_PRIEST_H

#include "Server/Model/Factory.h"
#include "ItemSeller.h"

class Priest: public ItemSeller {
    std::vector<Position> positions;
public:
    Priest() = default;
    Priest(std::vector<Position> positions, std::map<std::string, item_t> stock ,
           ItemFactory* itemFactory);
    void restoreManaAndLife(PlayableCharacter* character);
    void revive(PlayableCharacter* character);
    void reviveIn(PlayableCharacter *character, const Position& position);
    bool ocupies(const Position& position);
    Position closestPositionTo(PlayableCharacter *player);
    ~Priest();

    void sendStockListTo(PlayableCharacter *pCharacter);
};


#endif //ARGENTUM_PRIEST_H

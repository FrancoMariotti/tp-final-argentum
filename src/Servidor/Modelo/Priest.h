#ifndef ARGENTUM_PRIEST_H
#define ARGENTUM_PRIEST_H

#include "Factory.h"
#include "ItemSeller.h"

class Priest: public ItemSeller {
    std::vector<Position> positions;
    std::map<std::string, item_t> stock;
    std::map<std::string, EquippableFactory*> factories;
public:
    Priest() = default;
    Priest(std::vector<Position> positions, std::map<std::string, item_t> stock ,
           std::map<std::string, EquippableFactory*> factories);
    Priest& operator=(const Priest&);
    Priest(Priest&& priest) noexcept ;
    Equippable* sell(const std::string& name, int *gold) override;
    void restoreManaAndLife(PlayableCharacter* character);
    void revive(PlayableCharacter* character);
    void reviveIn(PlayableCharacter *character, const Position& position);
    bool ocupies(const Position& position);
    Position closestPositionTo(PlayableCharacter *player);
    ~Priest();
};


#endif //ARGENTUM_PRIEST_H

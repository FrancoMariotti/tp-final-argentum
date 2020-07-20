#ifndef ARGENTUM_WEAPON_H
#define ARGENTUM_WEAPON_H

#include "Equippable.h"
#include "Server/Model/Map/Position.h"

class Equippable;
class Character;
class PlayableCharacter;

class Weapon : public Equippable {
        int lastDamage;
    protected:
        int calculateDamage(int strength);
    public:
        Weapon(std::string name, int id, int minDamage,int maxDamage, int goldCost);
        void equipTo(PlayableCharacter *character, int i) override;
        virtual int attack(Character *owner,Character *enemy,int strength,int level,float &mana,Position &holderPos) = 0;
        void unequipFrom(PlayableCharacter *character) override ;
        ~Weapon() override = default;

    int getLastDamage();
};


#endif //ARGENTUM_WEAPON_H

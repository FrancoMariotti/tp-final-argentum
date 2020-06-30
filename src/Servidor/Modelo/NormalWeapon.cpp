#include "NormalWeapon.h"
#include "PlayableCharacter.h"
#include "Npc.h"

NormalWeapon::NormalWeapon(std::string name, int minDamage,int maxDamage):Weapon(name, minDamage,maxDamage) {}

int NormalWeapon::attack(Character *enemy, int strength,int level, int &mana,Position &holderPos) {
    if(enemy->distanceTo(holderPos) == 1) {
        int damage = calculateDamage(strength);
        return enemy->receiveDamage(level, damage);
    }
    return 0;
}

NormalWeapon::~NormalWeapon() = default;

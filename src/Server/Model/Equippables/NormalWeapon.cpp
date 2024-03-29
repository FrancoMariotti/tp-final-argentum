#include <iostream>
#include "NormalWeapon.h"
#include "Server/Model/Character/PlayableCharacter.h"
#include "Server/Model/Character/Npc.h"

NormalWeapon::NormalWeapon(std::string name, int id, int minDamage,int maxDamage, int goldCost)
    :Weapon(name, id, minDamage,maxDamage, goldCost) {}

int NormalWeapon::attack(Character* owner,Character *enemy, int strength,int level, float &mana,Position &holderPos) {
    if(owner == enemy) return 0;
    if(enemy->distanceTo(holderPos) == 1) {
        int damage = calculateDamage(strength);
        return enemy->receiveDamage(level, damage);
    }
    return OBJETIVO_FUERA_DE_RANGO;
}

NormalWeapon::~NormalWeapon() = default;

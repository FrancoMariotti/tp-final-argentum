#include "MagicalWeapon.h"
#include "SpellType.h"
#include "Heal.h"
#include "Damage.h"

MagicalWeapon::MagicalWeapon(std::string name,SpellType*spellType, int minDamage, int maxDamage, int cost)
    :Weapon(name, minDamage,maxDamage),spellType(spellType) {
    this->cost = cost;
}

int MagicalWeapon::attack(Character *target,int strength,int level,int &mana,Position &holderPos) {
    if(mana < cost) return 0;
    mana -= cost;
    int xp = spellType->giveAbilityTo(this,target,strength,level);
    return xp;
}

int MagicalWeapon::use(Heal* spell,Character *target,int strength,int level) {
    target->restoreLife();
    return 0;
}

int MagicalWeapon::use(Damage* spell,Character *target,int strength,int level) {
    int damage = calculateDamage(strength);
    return target->receiveDamage(level,damage);
}

MagicalWeapon::~MagicalWeapon() = default;

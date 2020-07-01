#include "MagicalWeapon.h"
#include "SpellType.h"
#include "Heal.h"
#include "Damage.h"

MagicalWeapon::MagicalWeapon(std::string name,SpellType*spellType, int minDamage,
        int maxDamage, int cost, int goldCost)
    :Weapon(name, minDamage,maxDamage, goldCost),spellType(spellType) {
    this->cost = cost;
}

int MagicalWeapon::attack(Character *target,int strength,int level,float &mana,Position &holderPos) {
    if(mana < cost) return 0;
    mana -= cost;
    int damage = calculateDamage(strength);
    int xp = spellType->use(target,strength,level,damage);
    return xp;
}

MagicalWeapon::~MagicalWeapon() {
    delete spellType;
}

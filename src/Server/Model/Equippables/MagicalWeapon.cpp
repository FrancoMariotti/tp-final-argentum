#include "MagicalWeapon.h"
#include "Server/Model/Spells/SpellType.h"
#include "Server/Model/Spells/Heal.h"
#include "Server/Model/Spells/Damage.h"

MagicalWeapon::MagicalWeapon(std::string name, int id, SpellType*spellType, int minDamage,
        int maxDamage, int cost, int goldCost)
    :Weapon(name, id, minDamage,maxDamage, goldCost),spellType(spellType) {
    this->cost = cost;
}

int MagicalWeapon::attack(Character* owner,Character *target,int strength,int level,float &mana,Position &holderPos) {
    if(mana < cost) return 0;
    mana -= cost;
    int damage = calculateDamage(strength);
    int xp = spellType->use(owner,target,strength,level,damage);
    return xp;
}

MagicalWeapon::~MagicalWeapon() {
    delete spellType;
}

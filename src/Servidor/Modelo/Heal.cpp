#include "Heal.h"

int Heal::use(Character *target, int strength, int level,int damage) {
    target->restoreLife();
    return 0;
}

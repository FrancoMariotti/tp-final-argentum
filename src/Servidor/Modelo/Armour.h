//
// Created by franco on 19/6/20.
//

#ifndef ARGENTUM_ARMOUR_H
#define ARGENTUM_ARMOUR_H

#include <vector>
#include "Equippable.h"
#include "Protection.h"

class Protection;

class Armour {
    std::vector<Protection> protections;
public:
    Armour();
    /*Armour(int chestMinDef, int chestMaxDef, int shieldMinDef, int shieldMaxDef
    , int helmetMinDef, int helmetMaxDef);*/
    //Devuelve el danio final que recibira el personaje luego de defenderse
    //OTRA OPCION SERIA QUE DEVUELVA SOLAMENTE EL VALOR DE DEFENSA Y HACER LA RESTA EN OTRO LADO
    void equip(Protection protection);
    int use(int damage) const;
    ~Armour() = default;
    void unequip(Protection protection);

    std::string getName(int equipmentId);
};


#endif //ARGENTUM_ARMOUR_H

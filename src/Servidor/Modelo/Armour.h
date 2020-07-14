//
// Created by franco on 19/6/20.
//

#ifndef ARGENTUM_ARMOUR_H
#define ARGENTUM_ARMOUR_H


#include <vector>
#include "Protection.h"

class Armour {
    friend class PlayableCharacterFactory;
    std::vector<Protection*> protections;
    Protection defaultProtection;
public:
    Armour();
    /*Armour(int chestMinDef, int chestMaxDef, int shieldMinDef, int shieldMaxDef
    , int helmetMinDef, int helmetMaxDef);*/
    //Devuelve el danio final que recibira el personaje luego de defenderse
    //OTRA OPCION SERIA QUE DEVUELVA SOLAMENTE EL VALOR DE DEFENSA Y HACER LA RESTA EN OTRO LADO
    void equipTo(Protection* protection, PlayableCharacter* character);
    int use(int damage) const;
    ~Armour();
    void unequip(Protection* protection);
    std::string getName(int equipmentId);
    void unequipEveryProtectionFrom(PlayableCharacter *player);

    void getNames(std::vector<std::string>& protectionNames);
};


#endif //ARGENTUM_ARMOUR_H

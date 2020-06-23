//
// Created by franco on 19/6/20.
//

#ifndef ARGENTUM_ARMOUR_H
#define ARGENTUM_ARMOUR_H


//enum ArmourType {chest, shield, helmet};

class Armour {
    int chestMinDef, chestMaxDef;
    int shieldMinDef, shieldMaxDef;
    int helmetMinDef, helmetMaxDef;
public:
    Armour();
    Armour(int chestMinDef, int chestMaxDef, int shieldMinDef, int shieldMaxDef
    , int helmetMinDef, int helmetMaxDef);
    void equipChest(int minDef, int maxDef);
    void equipShield(int minDef, int maxDef);
    void equipHelmet(int minDef, int maxDef);
    //Devuelve el danio final que recibira el personaje luego de defenderse
    //OTRA OPCION SERIA QUE DEVUELVA SOLAMENTE EL VALOR DE DEFENSA Y HACER LA RESTA EN OTRO LADO
    int use(int damage) const;
    ~Armour() = default;
};


#endif //ARGENTUM_ARMOUR_H

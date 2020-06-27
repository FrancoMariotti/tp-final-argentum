//
// Created by franco on 25/6/20.
//

#include "Potion.h"

Potion::Potion(int value) : Equippable(value, value){}

void Potion::equipTo(PlayableCharacter *character, int index) {
    equipped = true;
    character->equip(this, index);
}

void Potion::unequipFrom(PlayableCharacter *character) {
    //LA POCION NO HACE NADA YA QUE NO SE PUEDE DESEQUIPAR
    //SIN E,MBARGO TENGO QUE DEFINIR EL METODO PORQUE ESTE ES UN METODO ABSTRACTO
    //DE LA CLASE EQUIPPABLE
}
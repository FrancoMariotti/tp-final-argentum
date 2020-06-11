//
// Created by franco on 11/6/20.
//

#include "Movilidad.h"
void Movible::move(Position& posicion,Mapa& mapa,Offset& offset) {
    Position siguiente(posicion);
    siguiente.aplicar(offset);
    mapa.mover(posicion,siguiente);
}

void NoMovible::move(Position& posicion,Mapa& mapa,Offset& offset) {}
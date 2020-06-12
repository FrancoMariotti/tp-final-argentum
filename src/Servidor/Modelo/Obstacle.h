//
// Created by franco on 11/6/20.
//

#ifndef ARGENTUM_OBSTACLE_H
#define ARGENTUM_OBSTACLE_H


#include "Position.h"

//NOSE SI HACE FALTA LA CLASE OBSTACLE QUIZAS CON USAR UN GAME OGJECT COMUN BASTA
//GAME OBJECT YA TIENE IMPLEMENTADO EL METODO COLLIDE WITH
class Obstacle {
    public:
        //LO IMPLEMENTO ASI NOMAS PARA PODER COMPILAR
        bool collideWith(Position position);
};


#endif //ARGENTUM_OBSTACLE_H

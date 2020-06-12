//
// Created by franco on 11/6/20.
//

#ifndef ARGENTUM_OBSTACLE_H
#define ARGENTUM_OBSTACLE_H


#include "Position.h"

class Obstacle {
    //Esta posicion representa la posicion de la esquina superior izquierda del obstaculo
    Position position;
    int lenght,width;
    public:
        Obstacle(int x, int y, int lenght, int width);
        bool ocupies(Position position);
};


#endif //ARGENTUM_OBSTACLE_H

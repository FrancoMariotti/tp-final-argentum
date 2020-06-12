//
// Created by franco on 11/6/20.
//

#ifndef ARGENTUM_OBSTACLE_H
#define ARGENTUM_OBSTACLE_H


#include "Position.h"

class Obstacle {
    //Esta posicion representa la posicion de la esquina superior izquierda del obstaculo
    Position position;
    int height,width;
    public:
        Obstacle(int x, int y, int height, int width);
        bool ocupies(Position pos);
};


#endif //ARGENTUM_OBSTACLE_H

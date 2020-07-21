//
// Created by franco on 8/6/20.
//

#ifndef ARGENTUM_DIRECCION_H
#define ARGENTUM_DIRECCION_H

#include <cstdlib>
#include <vector>

class Offset {
    int xOffset;
    int yOffset;
    public:
        Offset(int xOffset,int yOffset);
        int move_x(int x) const;
        int move_y(int y) const;
        //calcula un offset a partir de la posicion
        //inicial del offset.
        void approach();
        void randomDir();
        int getX();
        int getY();
        bool isZero() const;
};

#endif //ARGENTUM_DIRECCION_H
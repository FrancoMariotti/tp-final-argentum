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
        Offset(int xOffset,int yOffset):xOffset(xOffset),yOffset(yOffset){}

        int move_x(int x) const {
            return x + xOffset;
        }
        int move_y(int y) const {
            return  y + yOffset;
        }

        void approach() {
            if (abs(xOffset) >= abs(yOffset)) {
                xOffset /= (abs(xOffset));
                yOffset = 0;
            } else {
                yOffset /= (abs(yOffset));
                xOffset = 0;
            }
        }

        void randomDir() {
            std::vector<int> posibleOffsets = {-1, 0, 1};
            xOffset = posibleOffsets[rand()%3];
            yOffset = posibleOffsets[rand()%3];
        }

        bool isZero() const{
            return (this->xOffset == 0) && (this->yOffset == 0);
        }
};

#endif //ARGENTUM_DIRECCION_H

#ifndef ARGENTUM_POSITION_H
#define ARGENTUM_POSITION_H
#include "Offset.h"

class Position {
    int x,y;
    public:
        Position(int x,int y);
        void apply(Offset &offset);
        int distanceTo(Position& position) const;
        bool operator==(const Position& position) const;
        Position& operator=(const Position& position);
        Offset operator-(Position& position) const;
        int getX() const;
        int getY() const;
        ~Position();

    bool outOfBounds(int initialX, int finalX, int initialY, int finalY);
};


#endif //ARGENTUM_POSITION_H

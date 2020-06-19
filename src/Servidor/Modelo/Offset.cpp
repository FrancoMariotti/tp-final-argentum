#include <syslog.h>
#include "Offset.h"

Offset::Offset(int xOffset,int yOffset) {
    this->xOffset = xOffset;
    this->yOffset = yOffset;
    //syslog(LOG_INFO,"Se Crea Offset con valores xOffset: %d, yOffset:%d",xOffset,yOffset);
}

int Offset::move_x(int x) const {
    return x + xOffset;
}
int Offset::move_y(int y) const {
    return  y + yOffset;
}

void Offset::approach() {
    if (abs(xOffset) >= abs(yOffset)) {
        xOffset /= (abs(xOffset));
        yOffset = 0;
    } else {
        yOffset /= (abs(yOffset));
        xOffset = 0;
    }
}

void Offset::randomDir() {
    std::vector<int> posibleOffsets ({-1, 0, 1});
    xOffset = posibleOffsets[rand()%3];
    yOffset = posibleOffsets[rand()%3];
}

bool Offset::isZero() const{
    return (this->xOffset == 0) && (this->yOffset == 0);
}
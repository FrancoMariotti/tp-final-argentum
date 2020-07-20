//
// Created by franco on 11/6/20.
//

#include "Obstacle.h"

Obstacle::Obstacle(int x, int y, int height, int width)
    : position(x, y), height(height), width(width) {
}

bool Obstacle::ocupies(Position pos) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; ++j) {
            Offset offset(i, j);
            Position auxPos = position;
            auxPos.apply(offset);
            if (auxPos == pos) return true;
        }
    }
    return false;
}
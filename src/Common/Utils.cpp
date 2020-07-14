#include "Utils.h"
#include "random"

float Utils::random_real_number(float min,float max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(min,max);
    return dist(mt);
}

int Utils::random_int_number(int min,int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min,max);
    return dist(mt);
}
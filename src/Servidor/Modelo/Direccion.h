//
// Created by franco on 8/6/20.
//

#ifndef ARGENTUM_DIRECCION_H
#define ARGENTUM_DIRECCION_H

class Direccion {
    public:
        Direccion() {}
        virtual int mover_x(int x) = 0;
        virtual int mover_y(int y) = 0;
        ~Direccion() {}

};

class Arriba: public Direccion {
    public:
        int mover_x(int x) {
            return x;
        }
        int mover_y(int y) {
            return y - 1;
        }
};

class Derecha: public Direccion {
public:
    int mover_x(int x) {
        return x+1;
    }
    int mover_y(int y) {
        return y;
    }
};

class Izquierda: public Direccion {
public:
    int mover_x(int x) {
        return x-1;
    }
    int mover_y(int y) {
        return y;
    }
};

class Abajo: public Direccion {
public:
    int mover_x(int x) {
        return x;
    }
    int mover_y(int y) {
        return y+1;
    }
};

#endif //ARGENTUM_DIRECCION_H
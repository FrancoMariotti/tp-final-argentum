//
// Created by franco on 5/6/20.
//

#ifndef ARGENTUM_FILA_H
#define ARGENTUM_FILA_H
#include "vector"

class Fila {
    public:
        Fila(int cols);
        bool ocupar(int  columna);
        virtual ~Fila();
    private:
        std::vector<int> columnas;
};


#endif //ARGENTUM_FILA_H

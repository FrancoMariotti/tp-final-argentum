#ifndef ARGENTUM_MAPA_H
#define ARGENTUM_MAPA_H
#include "vector"
#include "Fila.h"
class Mapa {
    public:
        Mapa(int filas,int cols);
        bool ocupar_posicion(int x,int y);
        virtual ~Mapa();
    private:
        std::vector<Fila> matriz;
};


#endif //ARGENTUM_MAPA_H

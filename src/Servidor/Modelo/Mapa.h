#ifndef ARGENTUM_MAPA_H
#define ARGENTUM_MAPA_H
#include "vector"
#include "GameObject.h"

class Posicion;

class Mapa {
    int ancho;
    int alto;
    std::vector<Posicion*> mapa;
    public:
        Mapa(int ancho,int alto);
        void agregar(Posicion* posicion);
        void mover(Posicion& desde,Posicion& hasta);
        ~Mapa();
};

#endif //ARGENTUM_MAPA_H

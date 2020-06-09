#ifndef ARGENTUM_MAPA_H
#define ARGENTUM_MAPA_H
#include "vector"
#include "GameObject.h"

class Posicion;
class Colisionable;

class Mapa {
    int ancho;
    int alto;
    std::vector<Colisionable*> colisionables;
    public:
        Mapa(int ancho,int alto);
        void agregar(Colisionable* posicion);
        void mover(Posicion& actual,Posicion& hasta);
        ~Mapa();
};

#endif //ARGENTUM_MAPA_H

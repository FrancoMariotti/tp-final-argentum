#ifndef ARGENTUM_GAMEOBJECT_H
#define ARGENTUM_GAMEOBJECT_H

#include "Mapa.h"
#include "Direccion.h"

class Mapa;

class Posicion {
    float x,y;
    public:
        Posicion(float x,float y);
        void aplicar(Direccion *direccion);
        bool operator==(const Posicion& posicion);
        void operator=(Posicion& posicion);
        ~Posicion();
};

class Movilidad {
    public:
        virtual void mover(Posicion posicion,Mapa& mapa,Direccion *direccion) = 0;
};

class Movible: public Movilidad {
    public:
        void mover(Posicion posicion,Mapa& mapa,Direccion *direccion);
};

class NoMovible: public Movilidad {
    public:
        void mover(Posicion posicion,Mapa& mapa,Direccion *direccion);
};

class GameObject {
    protected:
    Posicion posicion;
    Mapa& mapa;
    public:
        GameObject(float x,float y,Mapa& mapa);
        Posicion get_posicion();
        bool colisiono(Posicion& posicionObj);
        std::vector<int> GameObject::getOffset(Posicion pos);
        ~GameObject();
};




#endif //ARGENTUM_GAMEOBJECT_H

#ifndef ARGENTUM_GAMEOBJECT_H
#define ARGENTUM_GAMEOBJECT_H

#include "Mapa.h"
#include "Direccion.h"

class Mapa;

class Posicion {
    int x,y;
    public:
        Posicion(int x,int y);
        void aplicar(Direccion *direccion);
        bool operator==(const Posicion& posicion);
        void operator=(Posicion& posicion);
        ~Posicion();
};

class Movible {
    virtual void mover(Direccion *direccion);
};

class NoMovible {
    virtual void mover(Direccion *direccion);
};

class GameObject {
    Posicion posicion;
    Mapa& mapa;
public:
    GameObject(int x,int y,Mapa& mapa);
    Posicion get_posicion();
    ~GameObject();
};

class Personaje: public GameObject,public Movible {
    int vida;
    public:
        explicit Personaje(int vida);
        void mover(Direccion *direccion);
};

class NoJugable: public Personaje {
    Criatura criatura;//state
};

class Jugable: public Personaje {
    Clase clase;
    Raza raza;
};


#endif //ARGENTUM_GAMEOBJECT_H

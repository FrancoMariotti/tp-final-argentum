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
        ~GameObject();
};

class PersonajeNpc: public GameObject {
    int vida;
    Movilidad *movilidad;
    //Criatura criatura
    public:
        PersonajeNpc(int vida,Movilidad* movilidad,float x,float y,Mapa& mapa);
};

class Personaje: public GameObject {
    //Clase clase
    //Raza raza
    int vida;
    Movilidad *movilidad;
    public:
        Personaje(int vida,Movilidad* movilidad,float x,float y,Mapa& mapa);
        void mover(Direccion* direccion);
};


#endif //ARGENTUM_GAMEOBJECT_H

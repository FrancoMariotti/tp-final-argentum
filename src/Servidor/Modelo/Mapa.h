#ifndef ARGENTUM_MAPA_H
#define ARGENTUM_MAPA_H
#include "vector"
#include "GameObject.h"

class Posicion;
class GameObject;

class Mapa {
    int ancho;
    int alto;
    std::vector<GameObject*> objetos;
    public:
        Mapa(int ancho,int alto);
        void agregar(GameObject* objeto);
        void mover(Posicion& actual,Posicion& hasta);
        ~Mapa();
};

#endif //ARGENTUM_MAPA_H

#include "Mapa.h"

Mapa::Mapa(int ancho,int alto):ancho(ancho),alto(alto) {}

void Mapa::agregar(GameObject* objeto) {
    objetos.push_back(objeto);
}

void Mapa::mover(Posicion& actual,Posicion& hasta) {
    std::vector<GameObject*>::iterator it;
    for (it = objetos.begin() ; it != objetos.end(); ++it) {
        if((*it)->colisiono(hasta)) return;
    }
    actual = hasta;
}

Mapa::~Mapa() {}

#include "Mapa.h"

Mapa::Mapa(int ancho,int alto):ancho(ancho),alto(alto) {}

void Mapa::agregar(Posicion* posicion) {
    ocupadas.push_back(posicion);
}

void Mapa::mover(Posicion& desde,Posicion& hasta) {
    std::vector<Posicion*>::iterator it;
    for (it = ocupadas.begin() ; it != ocupadas.end(); ++it) {
        if(*(*it) == hasta) return;
    }
    desde = hasta;
}

Mapa::~Mapa() {}

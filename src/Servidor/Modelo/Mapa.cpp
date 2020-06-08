#include "Mapa.h"

Mapa::Mapa(int ancho,int alto):ancho(ancho),alto(alto) {}

void Mapa::agregar(Posicion* posicion) {
    mapa.push_back(posicion);
}

void Mapa::mover(Posicion& desde,Posicion& hasta) {
    std::vector<Posicion*>::iterator it;
    for (it = mapa.begin() ; it != mapa.end(); ++it) {
        if(*(*it) == hasta) return;
    }
    desde = hasta;
}
Mapa::~Mapa() {}

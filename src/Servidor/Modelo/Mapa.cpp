#include "Mapa.h"

Mapa::Mapa(int ancho,int alto):ancho(ancho),alto(alto) {}

void Mapa::agregar(Colisionable* colisionable) {
    colisionables.push_back(colisionable);
}

void Mapa::mover(Posicion& actual,Posicion& hasta) {
    std::vector<Colisionable*>::iterator it;
    for (it = colisionables.begin() ; it != colisionables.end(); ++it) {
        if((*it)->colisionoCon(hasta)) return;
    }
    actual = hasta;
}

Mapa::~Mapa() {}

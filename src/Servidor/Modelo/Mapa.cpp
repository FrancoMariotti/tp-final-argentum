#include "Mapa.h"
#include "Fila.h"
Mapa::Mapa(int filas,int cols):matriz(filas,Fila(cols)) {}

bool Mapa::ocupar_posicion(int x,int y) {
    return this->matriz[y].ocupar(x);
}

Mapa::~Mapa() {}

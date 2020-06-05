//
// Created by franco on 5/6/20.
//
#include "Fila.h"
#define LIBRE 0
#define OCUPADO 0

Fila::Fila(int  cols): columnas(cols,LIBRE) {
    //std::fill (columnas.begin(),columnas.end(),LIBRE);
}

bool Fila::ocupar(int  columna) {
    columnas[columna] = OCUPADO;
    return false;
}

Fila::~Fila() {}

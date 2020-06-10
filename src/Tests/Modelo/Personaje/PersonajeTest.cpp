//
// Created by franco on 6/6/20.
//

#include "PersonajeTest.h"
#include "Servidor/Modelo/Mapa.h"

CPPUNIT_TEST_SUITE_REGISTRATION( PersonajeTest );

void PersonajeTest::setUp() {}

void PersonajeTest::testPersonajePuedeMoverseAUnPasoDeDistanciaEnTodasLasDirecciones() {
    Mapa mapa(3,3);
    Movilidad* movilidad= new Movible();
    Personaje personaje(20,movilidad,2,2,mapa);
    Direccion *direccion = new Arriba();
    personaje.mover(direccion);
    Posicion *siguiente = new Posicion(2,1);
    CPPUNIT_ASSERT(personaje.get_posicion() == *siguiente);
    delete direccion;
    delete siguiente;

    direccion = new Derecha();
    personaje.mover(direccion);
    siguiente = new Posicion(3,1);
    CPPUNIT_ASSERT(personaje.get_posicion() == *siguiente);
    delete direccion;
    delete siguiente;

    direccion = new Abajo();
    personaje.mover(direccion);
    siguiente = new Posicion(3,2);
    CPPUNIT_ASSERT(personaje.get_posicion() == *siguiente);
    delete direccion;
    delete siguiente;

    direccion = new Izquierda();
    personaje.mover(direccion);
    siguiente = new Posicion(2,2);
    CPPUNIT_ASSERT(personaje.get_posicion() == *siguiente);
    delete direccion;
    delete siguiente;
}
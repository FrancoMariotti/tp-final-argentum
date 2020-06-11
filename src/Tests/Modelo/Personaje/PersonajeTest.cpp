//
// Created by franco on 6/6/20.
//

#include "PersonajeTest.h"
#include "Servidor/Modelo/Mapa.h"
#include "Servidor/Modelo/Movilidad.h"
#include "Servidor/Modelo/PlayableCharacter.h"

CPPUNIT_TEST_SUITE_REGISTRATION( PersonajeTest );

void PersonajeTest::setUp() {}

void PersonajeTest::testPersonajePuedeMoverseAUnPasoDeDistanciaEnTodasLasDirecciones() {
    Mapa mapa(10,10);
    Movilidad* movilidad= new Movible();
    PlayableCharacter player(20,movilidad,2,2,mapa);

    {
        //test:el personaje se mueve hacia arriba en el mapa
        Offset offset(0,-1);
        player.move(offset);
        Position next(2,1);
        CPPUNIT_ASSERT(player.actual == next);
    }

    {
        //test:el personaje se mueve hacia la derecha en el mapa
        Offset offset(1,0);
        player.move(offset);
        Position next(3,1);
        CPPUNIT_ASSERT(player.actual == next);
    }

    {
        //test:el personaje se mueve hacia la abajo en el mapa
        Offset offset(0,1);
        player.move(offset);
        Position next(3,2);
        CPPUNIT_ASSERT(player.actual == next);
    }

    {
        //test:el personaje se mueve hacia la izquierda en el mapa
        Offset offset(-1,0);
        player.move(offset);
        Position next(2,2);
        CPPUNIT_ASSERT(player.actual == next);
    }
}
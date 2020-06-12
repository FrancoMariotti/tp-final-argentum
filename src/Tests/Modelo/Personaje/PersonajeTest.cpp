//
// Created by franco on 6/6/20.
//

#include "PersonajeTest.h"
#include "Servidor/Modelo/Map.h"
#include "Servidor/Modelo/Mobility.h"
#include "Servidor/Modelo/PlayableCharacter.h"

CPPUNIT_TEST_SUITE_REGISTRATION( PersonajeTest );

void PersonajeTest::setUp() {}

void PersonajeTest::testPersonajePuedeMoverseAUnPasoDeDistanciaEnTodasLasDirecciones() {
    Map map(10, 10);
    Mobility* mobility= new Movable();
    PlayableCharacter player(20,mobility,2,2,map);

    {
        //test:el personaje se mueve hacia arriba en el map
        Offset offset(0,-1);
        player.move(offset);
        Position next(2,1);
        CPPUNIT_ASSERT(player.currPos == next);
    }

    {
        //test:el personaje se mueve hacia la derecha en el map
        Offset offset(1,0);
        player.move(offset);
        Position next(3,1);
        CPPUNIT_ASSERT(player.currPos == next);
    }

    {
        //test:el personaje se mueve hacia la abajo en el map
        Offset offset(0,1);
        player.move(offset);
        Position next(3,2);
        CPPUNIT_ASSERT(player.currPos == next);
    }

    {
        //test:el personaje se mueve hacia la izquierda en el map
        Offset offset(-1,0);
        player.move(offset);
        Position next(2,2);
        CPPUNIT_ASSERT(player.currPos == next);
    }
}
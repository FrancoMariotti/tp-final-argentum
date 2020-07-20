//
// Created by franco on 6/6/20.
//
/*
#include "PersonajeTest.h"
#include "Server/Model/Map.h"
#include "Server/Model/Mobility.h"
#include "Server/Model/PlayableCharacter.h"

CPPUNIT_TEST_SUITE_REGISTRATION( PersonajeTest );

void PersonajeTest::setUp() {}

void PersonajeTest::testPersonajePuedeMoverseAUnPasoDeDistanciaEnTodasLasDirecciones() {
    Map map(10, 10);
    Position pos(1,1);
    //INICIALIZO LOS FACTORES CON 0 PORQUE PARA ESTA PRUEBA NO SON NECESARIOS
    PlayableCharacter player(&map, 20,pos , 2,2,18,18,18,
            18,0 ,0, 0,
            0, 0);

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

void PersonajeTest::testPersonajeNoPuedeirseDelMapa() {

    Map map(10, 10);
    Position pos(1, 1);
    //INICIALIZO LOS FACTORES CON 0 PORQUE PARA ESTA PRUEBA NO SON NECESARIOS
    PlayableCharacter player(&map, 20,pos ,0,0,18,18,18,
                             18,0 ,0, 0,
                             0, 0);

    {
        //test:el personaje se mueve hacia arriba en el map
        Offset offset(0,-1);
        player.move(offset);
        Position next(0,0);
        CPPUNIT_ASSERT(player.currPos == next);
    }
}
 */
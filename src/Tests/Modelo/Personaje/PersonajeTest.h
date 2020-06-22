//
// Created by franco on 6/6/20.
//

#ifndef ARGENTUM_PERSONAJETEST_H
#define ARGENTUM_PERSONAJETEST_H
#include <cppunit/extensions/HelperMacros.h>
#include <Servidor/Modelo/PlayableCharacter.h>


class PersonajeTest :  public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( PersonajeTest );
    CPPUNIT_TEST( testPersonajePuedeMoverseAUnPasoDeDistanciaEnTodasLasDirecciones );
    CPPUNIT_TEST( testPersonajeNoPuedeirseDelMapa );
    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();

    protected:
        void testPersonajePuedeMoverseAUnPasoDeDistanciaEnTodasLasDirecciones();
        void testPersonajeNoPuedeirseDelMapa();

};


#endif //ARGENTUM_PERSONAJETEST_H

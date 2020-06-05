//
// Created by franco on 5/6/20.
//

#ifndef ARGENTUM_MAPATEST_H
#define ARGENTUM_MAPATEST_H
#include <cppunit/extensions/HelperMacros.h>

class MapaTest : public CppUnit::TestFixture  {
    CPPUNIT_TEST_SUITE( MapaTest );
    CPPUNIT_TEST( testOccupy );
    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();
    protected:
        void testOccupy();
};
#endif //ARGENTUM_MAPATEST_H

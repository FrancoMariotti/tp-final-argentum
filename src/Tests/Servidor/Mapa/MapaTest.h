//
// Created by franco on 5/6/20.
//

#ifndef ARGENTUM_MAPATEST_H
#define ARGENTUM_MAPATEST_H
#include <cppunit/extensions/HelperMacros.h>

class MapaTest :  public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( MapaTest );
    CPPUNIT_TEST( example );
    CPPUNIT_TEST( anotherExample );
    CPPUNIT_TEST( testAdd );
    CPPUNIT_TEST( testEquals );
    CPPUNIT_TEST_SUITE_END();

    protected:
        double m_value1;
        double m_value2;

    public:
        void setUp();

    protected:
        void example();
        void anotherExample();
        void testAdd();
        void testEquals();
};
#endif //ARGENTUM_MAPATEST_H

//
// Created by franco on 5/6/20.
//
#include <cppunit/config/SourcePrefix.h>
#include "MapaTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION( MapaTest );

void MapaTest::setUp() {
    m_value1 = 2.0;
    m_value2 = 3.0;
}


void MapaTest::example() {
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 1.0, 1.1, 0.05 );
    CPPUNIT_ASSERT( 1 == 0 );
    CPPUNIT_ASSERT( 1 == 1 );
}


void MapaTest::anotherExample() {
    CPPUNIT_ASSERT (1 == 2);
}

void MapaTest::testEquals()
{
    long* l1 = new long(12);
    long* l2 = new long(12);

    CPPUNIT_ASSERT_EQUAL( 12, 12 );
    CPPUNIT_ASSERT_EQUAL( 12L, 12L );
    CPPUNIT_ASSERT_EQUAL( *l1, *l2 );

    delete l1;
    delete l2;

    CPPUNIT_ASSERT( 12L == 12L );
    CPPUNIT_ASSERT_EQUAL( 12, 13 );
    CPPUNIT_ASSERT_DOUBLES_EQUAL( 12.0, 11.99, 0.5 );
}



void MapaTest::testAdd()
{
    double result = m_value1 + m_value2;
    CPPUNIT_ASSERT( result == 6.0 );
}

class FixtureTest : public CPPUNIT_NS::TestFixture
{
};

CPPUNIT_TEST_FIXTURE(FixtureTest, testEquals)
{
    CPPUNIT_ASSERT_EQUAL( 12, 12 );
}

CPPUNIT_TEST_FIXTURE(FixtureTest, testAdd)
{
    double result = 2.0 + 2.0;
    CPPUNIT_ASSERT( result == 4.0 );
}
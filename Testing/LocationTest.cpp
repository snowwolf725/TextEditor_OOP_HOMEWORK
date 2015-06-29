#include "LocationTest.h"
#include <string>
using namespace std;
// Registers the fixture into the 'registry' 
CPPUNIT_TEST_SUITE_REGISTRATION( LocationTest ); 
void LocationTest::setUp() { loc=new Location(); } 
void LocationTest::tearDown() { delete loc; } 
void LocationTest::testSetX() 
{
  // Check
  loc->setX(10);
  CPPUNIT_ASSERT_EQUAL( 10, loc->getX() );
  loc->setX(-10);
  CPPUNIT_ASSERT_EQUAL( -10, loc->getX() );
  loc->setX(0);
  CPPUNIT_ASSERT_EQUAL( 0, loc->getX() );
}

void LocationTest::testSetY() 
{
  // Check
  loc->setY(5);
  CPPUNIT_ASSERT_EQUAL( 5, loc->getY() );
  loc->setY(-5);
  CPPUNIT_ASSERT_EQUAL( -5, loc->getY() );
  loc->setY(0);
  CPPUNIT_ASSERT_EQUAL( 0, loc->getY() );
}

void LocationTest::testToString() 
{
  // Set up
  const int x=-5;
  const int y=10;
  
  // Process
  loc->setX(x);
  loc->setY(y);
  // Check
  CPPUNIT_ASSERT_EQUAL( string("(11, -4)"), loc->toString() );
}


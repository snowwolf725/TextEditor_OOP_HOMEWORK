#ifndef _LOCATIONTEST_H_
#define _LOCATIONTEST_H_
#include <cppunit/extensions/HelperMacros.h> 
#include "../Location.h"

class LocationTest : public CppUnit::TestFixture 
{ 
	CPPUNIT_TEST_SUITE( LocationTest );
	CPPUNIT_TEST( testSetX );
	CPPUNIT_TEST( testSetY );
	CPPUNIT_TEST( testToString );
	CPPUNIT_TEST_SUITE_END();
public:
    void setUp(); 
    void tearDown(); 
    void testSetX(); 
    void testSetY();
    void testToString();
private:
	Location *loc;
}; 
#endif //_LOCATIONTEST_H_

#ifndef _TEXTLOCATIONMAP_TEST_H_
#define _TEXTLOCATIONMAP_TEST_H_
#include <cppunit/extensions/HelperMacros.h> 
#include "../TextLocationMap_Imp.h"

class TextLocationMap_Test : public CppUnit::TestFixture 
{ 
	CPPUNIT_TEST_SUITE( TextLocationMap_Test );
	CPPUNIT_TEST( testGetLocationSet );
	CPPUNIT_TEST( testGetLocationSet2 );
	CPPUNIT_TEST_SUITE_END();
public:
    void setUp(); 
    void tearDown(); 
    void testGetLocationSet();
    void testGetLocationSet2();
private:
	TextLocationMap_Imp *tlocmap;
}; 
#endif //_TEXTLOCATIONMAPTEST_H_

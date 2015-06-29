#ifndef _TEXTLOCATIONMAPBUILDERTEST_H_
#define _TEXTLOCATIONMAPBUILDERTEST_H_

#include <cppunit/extensions/HelperMacros.h> 
#include <vector>
#include <string>
#include "../Location.h"
#include "../TextLocationMapBuilder_Imp.h"
#include "TextLocationMap_Mock.h"

using namespace std;

class TextLocationMapBuilderTest : public CppUnit::TestFixture 
{ 
	CPPUNIT_TEST_SUITE( TextLocationMapBuilderTest );
	CPPUNIT_TEST( testBuild );
	CPPUNIT_TEST_SUITE_END();
public:
    void setUp(); 
    void tearDown(); 
    void testBuild();
private:
	TextLocationMap_Mock *tlocmap;
	TextLocationMapBuilder_Imp *tlocmap_builder;
}; 

#endif //_TEXTLOCATIONMAPBUILDERTEST_H_

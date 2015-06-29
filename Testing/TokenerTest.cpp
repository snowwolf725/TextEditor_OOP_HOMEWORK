#include "TokenerTest.h"
#include <string>
using namespace std;
// Registers the fixture into the 'registry' 
CPPUNIT_TEST_SUITE_REGISTRATION( TokenerTest ); 
void TokenerTest::setUp() {tok=new Tokener();} 
void TokenerTest::tearDown() {delete tok;} 
void TokenerTest::testParsing() //for []
{
	// Set up
	tok->parsing("test test2");
	// Process
	// Check
	CPPUNIT_ASSERT_EQUAL( string("test") , (*tok)[0]);
}

void TokenerTest::testSize()
{
	// Set up
	tok->parsing("test test2");
	// Process
	// Check
	CPPUNIT_ASSERT_EQUAL( 2 , tok->size());	
}

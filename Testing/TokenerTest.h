#ifndef _TOKENERTEST_H_
#define _TOKENERTEST_H_
#include <cppunit/extensions/HelperMacros.h> 
#include "../Tokener.h"

class TokenerTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( TokenerTest );
	CPPUNIT_TEST( testParsing );
	CPPUNIT_TEST( testSize );
	CPPUNIT_TEST_SUITE_END();
public:
    void setUp(); 
    void tearDown(); 
    void testParsing();
    void testSize();
private:
	Tokener *tok;
};
#endif //_TOKENERTEST_H_

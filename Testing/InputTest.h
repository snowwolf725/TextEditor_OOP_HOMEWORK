#ifndef INPUTTEST_H 
#define INPUTTEST_H 
#include <cppunit/extensions/HelperMacros.h> 
#include "../Input.h"
#include "../Display.h"
#include "../Text.h"
#include "../Tokener.h"

class InputTest : public CppUnit::TestFixture 
{ 
	CPPUNIT_TEST_SUITE( InputTest );
//	CPPUNIT_TEST( testDispatchCommand );
	CPPUNIT_TEST_SUITE_END();
	
public:
    void setUp();
    void tearDown();
    void testDispatchCommand();
private:
	Input *m_pInput;
}; 
#endif // INPUTTEST_H

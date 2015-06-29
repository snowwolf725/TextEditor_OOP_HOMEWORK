#ifndef _SPELLCHECKER_TEST_H_
#define _SPELLCHECKER_TEST_H_

#include <cppunit/extensions/HelperMacros.h> 
#include "../SpellChecker.h"
#include "Display_Mock.h"

class SpellChecker_Test : public CppUnit::TestFixture 
{ 
	CPPUNIT_TEST_SUITE( SpellChecker_Test );
	CPPUNIT_TEST( testLoadDict1 );
	CPPUNIT_TEST( testLoadDict2 );
	CPPUNIT_TEST( testSpellChecker1 );
	CPPUNIT_TEST( testSpellChecker2 );
	CPPUNIT_TEST( testFindSugges1 );
	CPPUNIT_TEST( testFindSugges2 );
	CPPUNIT_TEST( testFindSugges3 );
	CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
    void testLoadDict1();
    void testLoadDict2();
    void testSpellChecker1();
    void testSpellChecker2();
    void testFindSugges1();
    void testFindSugges2();
    void testFindSugges3();
private:
	SpellChecker	*m_pState;
	Display		*m_pDisplay;
};

#endif //_SPELLCHECKER_TEST_H_

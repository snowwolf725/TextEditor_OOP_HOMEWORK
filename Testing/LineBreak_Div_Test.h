#ifndef _LINEBREAK_DIV_TEST_H_
#define _LINEBREAK_DIV_TEST_H_

#include <cppunit/extensions/HelperMacros.h> 
#include "../LineBreak_Div.h"

class LineBreak_Div_Test : public CppUnit::TestFixture 
{ 
	CPPUNIT_TEST_SUITE( LineBreak_Div_Test );
	CPPUNIT_TEST( testCheck1 );
	CPPUNIT_TEST( testCheck2 );
	CPPUNIT_TEST( testSetWidth1 );
	CPPUNIT_TEST( testSetWidth2 );
	CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
    void testCheck1();
    void testCheck2();
    void testSetWidth1();
    void testSetWidth2();
private:
	vector<string> *m_pTexts;
	LineBreak_Div	*m_pLineBreak;
};

#endif //_LINEBREAK_DIV_TEST_H_

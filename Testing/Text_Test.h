#ifndef _TEXT_TEST_H_
#define _TEXT_TEST_H_
#include <cppunit/extensions/HelperMacros.h> 
#include "../Text.h"
#include "Display_Mock.h"
#include "Cursor_Mock.h"

class Text_Test : public CppUnit::TestFixture 
{ 
	CPPUNIT_TEST_SUITE( Text_Test );
	CPPUNIT_TEST( testSetPos1 );
	CPPUNIT_TEST( testSetPos2 );
	CPPUNIT_TEST( testCompact1 );
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp(); 
	void tearDown(); 
	void testSetPos1();
	void testSetPos2();
	void testCompact1();
private:
	Text *m_pText;
	Display *m_pDisplay;
	Cursor *m_pCursor;
	vector<string> *m_pTexts;
};
#endif //_TEXT_TEST_H_

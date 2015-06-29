#include "Text_Test.h"
#include <string>
using namespace std;
// Registers the fixture into the 'registry' 
CPPUNIT_TEST_SUITE_REGISTRATION( Text_Test ); 
void Text_Test::setUp() 
{
	m_pText=new Text_Imp();
	m_pDisplay=new Display_Mock();
	m_pCursor=new Cursor_Mock();
	m_pText->setDisplay(m_pDisplay);
	m_pText->setCursor(m_pCursor);
	
	m_pText->readFile("testing.txt");
	m_pTexts=m_pText->getTexts();
} 

void Text_Test::tearDown() 
{
	delete m_pText; 
	delete m_pDisplay;
	//m_pTexts will realse in Text
} 

void Text_Test::testSetPos1() 
{
	// Set up
	// Process
	// Check
	CPPUNIT_ASSERT_EQUAL( m_pText->setPos(0,0),0);
}

void Text_Test::testSetPos2() 
{
	// Set up
	// Process
	// Check
	CPPUNIT_ASSERT_EQUAL( m_pText->setPos(1,-2),1);
}

void Text_Test::testCompact1() 
{
	// Set up
	int ischeck;
	string cmp=" test";
	string res;
	// Process
	m_pText->compact();
	res=(*m_pTexts)[0];
	ischeck= cmp.compare(res);
	// Check
	CPPUNIT_ASSERT_EQUAL( ischeck,0 );
}

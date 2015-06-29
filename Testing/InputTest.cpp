#include "InputTest.h"
using namespace std;
// Registers the fixture into the 'registry' 
CPPUNIT_TEST_SUITE_REGISTRATION( InputTest ); 
void InputTest::setUp() {/*m_pInput=new Input(); */} 
void InputTest::tearDown() {/*delete m_pInput; */} 
void InputTest::testDispatchCommand() 
{
	// Set up
	Tokener tok;
	tok.parsing( "test.txt" );
//	Text_Imp *t=new Text_Imp();
//	Display *d=new Display_Imp();
//	t->setDisplay(d);
//	m_pInput->setText(t);
//	m_pInput->dispatchCommand(string("open"),tok);
	// Check
//	CPPUNIT_ASSERT_EQUAL( m_pInput->dispatchCommand(string("!"),tok),true);
}


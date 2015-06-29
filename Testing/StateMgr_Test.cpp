#include "StateMgr_Test.h"
#include <string>
using namespace std;
// Registers the fixture into the 'registry' 
CPPUNIT_TEST_SUITE_REGISTRATION( StateMgr_Test ); 
void StateMgr_Test::setUp()
{
	m_pState=StateMgr::getInstance();
} 
void StateMgr_Test::tearDown() 
{ 
	delete m_pState;
} 

void StateMgr_Test::testSetGUIState1() 
{
  // Set up
  bool result=false;
  // Process
  m_pState->setGUIState(true);
  result=m_pState->getGUIState();
  // Check
  CPPUNIT_ASSERT_EQUAL( result,true );
}


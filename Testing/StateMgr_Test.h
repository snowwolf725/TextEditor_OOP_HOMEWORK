#ifndef _STATEMGR_TEST_H_
#define _STATEMGR_TEST_H_

#include <cppunit/extensions/HelperMacros.h> 
#include "../StateMgr.h"

class StateMgr_Test : public CppUnit::TestFixture 
{ 
	CPPUNIT_TEST_SUITE( StateMgr_Test );
	CPPUNIT_TEST( testSetGUIState1 );
	CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
    void testSetGUIState1();
private:
	StateMgr *m_pState;
};

#endif //_STATEMGR_TEST_H_

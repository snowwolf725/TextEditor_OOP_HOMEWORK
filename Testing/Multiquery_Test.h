#ifndef _MULTIQUERY_TEST_H_
#define _MULTIQUERY_TEST_H_
#include <cppunit/extensions/HelperMacros.h> 
#include "../Multiquery.h"
#include "../Tokener.h"

class Multiquery_Test : public CppUnit::TestFixture 
{ 
	CPPUNIT_TEST_SUITE( Multiquery_Test );
	CPPUNIT_TEST( notQuery1 );
	CPPUNIT_TEST( notQuery2 );
	CPPUNIT_TEST( andQuery1 );
	CPPUNIT_TEST( andQuery2 );
	CPPUNIT_TEST( orQuery1 );
	CPPUNIT_TEST( orQuery2 );
//	CPPUNIT_TEST( parsering1 );
//	CPPUNIT_TEST( parsering2 );	
	CPPUNIT_TEST( checkop1 );
	CPPUNIT_TEST( checkstack );
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();
	void notQuery1();
	void notQuery2();
	void andQuery1();
	void andQuery2();	
	void orQuery1();
	void orQuery2();	
	void parsering1();
	void parsering2();
	void checkop1();
	void checkstack();
private:
	Multiquery *que;
};

#endif //_MULTIQUERY_TEST_H_

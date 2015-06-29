#ifndef _QUERY_TEST_H_
#define _QUERY_TEST_H_
#include <cppunit/extensions/HelperMacros.h> 
#include "../Query.h"

class Query_Test : public CppUnit::TestFixture 
{ 
	CPPUNIT_TEST_SUITE( Query_Test );
	CPPUNIT_TEST( testSingleQuery1 );
	CPPUNIT_TEST( testSingleQuery2 );
	CPPUNIT_TEST( testFuzzyQuery1 );
	CPPUNIT_TEST( testFuzzyQuery2 );
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();
	void testSingleQuery1();
	void testSingleQuery2();
	void testFuzzyQuery1();
	void testFuzzyQuery2();
private:
	Query *que;
};

#endif //_QUERY_TEST_H_

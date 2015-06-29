#include "Query_Test.h"
#include <string>
using namespace std;
// Registers the fixture into the 'registry' 
CPPUNIT_TEST_SUITE_REGISTRATION( Query_Test ); 
void Query_Test::setUp() { que=new Query(); } 
void Query_Test::tearDown() { delete que; } 

void Query_Test::testSingleQuery1() 
{
  // Set up
  vector<string> teststring;
  string qstr("second.");
  teststring.push_back("Release date of this version: August/14/2002");
  teststring.push_back("The program provides 10 independent timers, for counting down");
  teststring.push_back("or up. They can run up to 100 hours with an accuracy of 1 second.");
  // Process
  que->singleQuery(qstr,&teststring);
  vector<int> result=que->getAns();
  // Check
  CPPUNIT_ASSERT_EQUAL( result[0],2 );
}

void Query_Test::testSingleQuery2() 
{
  // Set up
  vector<string> teststring;
  string qstr("notfound.");
  teststring.push_back("Release date of this version: August/14/2002");
  teststring.push_back("The program provides 10 independent timers, for counting down");
  teststring.push_back("or up. They can run up to 100 hours with an accuracy of 1 second.");
  // Process
  que->singleQuery(qstr,&teststring);
  vector<int> result=que->getAns();
  // Check
  int test=result.size();
  CPPUNIT_ASSERT_EQUAL( test,0 );
}

void Query_Test::testFuzzyQuery1() 
{
  // Set up
  vector<string> teststring;
  string qstr("1*0*");
  teststring.push_back("Release date of this version: August/14/2002");
  teststring.push_back("The program provides 10 independent timers, for counting down");
  teststring.push_back("or up. They can run up to 100 hours with an accuracy of 1 second.");
  // Process
  que->fuzzyQuery(qstr,&teststring);
  vector<int> result=que->getAns();
  // Check
  int result_count=result.size();
  CPPUNIT_ASSERT_EQUAL( result_count,3 );
  CPPUNIT_ASSERT_EQUAL( result[0],0 );
  CPPUNIT_ASSERT_EQUAL( result[1],1 );
  CPPUNIT_ASSERT_EQUAL( result[2],2 );
}

void Query_Test::testFuzzyQuery2() 
{
  // Set up
  vector<string> teststring;
  string qstr("*not*found.*");
  teststring.push_back("Release date of this version: August/14/2002");
  teststring.push_back("The program provides 10 independent timers, for counting down");
  teststring.push_back("or up. They can run up to 100 hours with an accuracy of 1 second.");
  // Process
  que->singleQuery(qstr,&teststring);
  vector<int> result=que->getAns();
  // Check
  int test=result.size();
  CPPUNIT_ASSERT_EQUAL( test,0 );
}

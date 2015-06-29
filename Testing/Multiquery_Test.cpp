#include "Multiquery_Test.h"
#include <string>
using namespace std;
// Registers the fixture into the 'registry' 
CPPUNIT_TEST_SUITE_REGISTRATION( Multiquery_Test ); 
void Multiquery_Test::setUp() { que=new Multiquery(); } 
void Multiquery_Test::tearDown() { delete que; } 

void Multiquery_Test::notQuery1() 
{
  // Set up
  vector<string> teststring;
  vector<int> result;
  vector<int> find_loc;
  string qstr("second.");
  teststring.push_back("Release date of this version: August/14/2002");
  teststring.push_back("The program provides 10 independent timers, for counting down");
  teststring.push_back("or up. They can run up to 100 hours with an accuracy of 1 second.");
  que->m_pTexts=&teststring;
  find_loc.push_back(0);
  find_loc.push_back(2);
  // Process
  result=que->notQuery(find_loc);
  // Check
  CPPUNIT_ASSERT_EQUAL( result[0],1 );
}

void Multiquery_Test::notQuery2() 
{
  // Set up
  vector<string> teststring;
  vector<int> result;
  vector<int> find_loc;
  string qstr("second.");
  teststring.push_back("Release date of this version: August/14/2002");
  teststring.push_back("The program provides 10 independent timers, for counting down");
  teststring.push_back("or up. They can run up to 100 hours with an accuracy of 1 second.");
  que->m_pTexts=&teststring;
  // Process
  result=que->notQuery(find_loc);
  // Check
  int count=result.size();
  CPPUNIT_ASSERT_EQUAL( count,3 );
}

void Multiquery_Test::andQuery1() 
{
  // Set up
  vector<int> result;
  vector<int> find_loc1;
  vector<int> find_loc2;
  find_loc1.push_back(1);
  find_loc1.push_back(2);
  find_loc1.push_back(3);
  find_loc2.push_back(2);
  // Process
  result=que->andQuery(find_loc1,find_loc2);
  // Check
  int count=result.size();
  CPPUNIT_ASSERT_EQUAL( count,1 );
  CPPUNIT_ASSERT_EQUAL( result[0],2 );
}

void Multiquery_Test::andQuery2() 
{
  // Set up
  vector<int> result;
  vector<int> find_loc1;
  vector<int> find_loc2;
  find_loc1.push_back(1);
  find_loc1.push_back(2);
  find_loc1.push_back(3);
  find_loc2.push_back(4);
  // Process
  result=que->andQuery(find_loc1,find_loc2);
  // Check
  int count=result.size();
  CPPUNIT_ASSERT_EQUAL( count,0 );
}

void Multiquery_Test::orQuery1() 
{
  // Set up
  vector<int> result;
  vector<int> find_loc1;
  vector<int> find_loc2;
  find_loc1.push_back(1);
  find_loc1.push_back(2);
  find_loc2.push_back(2);
  find_loc2.push_back(3);
  // Process
  result=que->orQuery(find_loc1,find_loc2);
  // Check
  int count=result.size();
  CPPUNIT_ASSERT_EQUAL( count,3 );
  CPPUNIT_ASSERT_EQUAL( result[0],1 );
  CPPUNIT_ASSERT_EQUAL( result[1],2 );
  CPPUNIT_ASSERT_EQUAL( result[2],3 );
}

void Multiquery_Test::orQuery2() 
{
  // Set up
  vector<int> result;
  vector<int> find_loc1;
  vector<int> find_loc2;
  // Process
  result=que->orQuery(find_loc1,find_loc2);
  // Check
  int count=result.size();
  CPPUNIT_ASSERT_EQUAL( count,0 );
}

void Multiquery_Test::parsering1()
{
  // Set up
  Tokener tok;
  tok.parsing("( daddy && emma )");
  vector<string> teststring;
  vector<int> find_loc;
  teststring.push_back("Release date of this version: August/14/2002");
  teststring.push_back("The program provides 10 independent timers, for counting down");
  teststring.push_back("or up. They can run up to 100 hours with an accuracy of 1 second.");
  que->m_pTexts=&teststring;
  cout<<(*que->m_pTexts)[0]<<endl;
  // Process
  bool result=que->parsering(tok);
  // Check
  CPPUNIT_ASSERT_EQUAL( result,true );
}

void Multiquery_Test::parsering2()
{
  // Set up
  Tokener tok;
  tok.parsing("( daddy && emma f)");
  vector<string> teststring;
  vector<int> find_loc;
  teststring.push_back("Release date of this version: August/14/2002");
  teststring.push_back("The program provides 10 independent timers, for counting down");
  teststring.push_back("or up. They can run up to 100 hours with an accuracy of 1 second.");
  que->m_pTexts=&teststring;
  // Process
  bool result=que->parsering(tok);
  // Check
  CPPUNIT_ASSERT_EQUAL( result,false);
}

void Multiquery_Test::checkop1()
{
  // Set up
  string qstr="emma";
  string qstr1=")";
  string qstr2_1="||";
  string qstr2_2="&&";
  string qstr3="!";
  string qstr4="(";
  // Process
  int result=que->checkop(qstr);
  int result1=que->checkop(qstr1);
  int result2_1=que->checkop(qstr2_1);
  int result2_2=que->checkop(qstr2_2);
  int result3=que->checkop(qstr3);
  int result4=que->checkop(qstr4);
  // Check
  CPPUNIT_ASSERT_EQUAL( result,0);
  CPPUNIT_ASSERT_EQUAL( result1,1);
  CPPUNIT_ASSERT_EQUAL( result2_1,2);
  CPPUNIT_ASSERT_EQUAL( result2_2,2);
  CPPUNIT_ASSERT_EQUAL( result3,3);
  CPPUNIT_ASSERT_EQUAL( result4,4);
}

void Multiquery_Test::checkstack()
{
  // Set up
  que->m_operator.push("(");
  que->m_operator.push("||");
  que->m_operator.push("&&");
  que->m_operator.push("!");
  // Process
  int result=que->checkstack();
  // Check
  CPPUNIT_ASSERT_EQUAL( result,3);
  que->m_operator.pop();
  result=que->checkstack();
  CPPUNIT_ASSERT_EQUAL( result,2);
  que->m_operator.pop();
  result=que->checkstack();
  CPPUNIT_ASSERT_EQUAL( result,2);
  que->m_operator.pop();
  result=que->checkstack();
  CPPUNIT_ASSERT_EQUAL( result,1);
  que->m_operator.pop();
  result=que->checkstack();
  CPPUNIT_ASSERT_EQUAL( result,0);
}  

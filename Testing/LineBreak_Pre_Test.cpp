#include "LineBreak_Pre_Test.h"
#include <string>
using namespace std;
// Registers the fixture into the 'registry' 
CPPUNIT_TEST_SUITE_REGISTRATION( LineBreak_Pre_Test ); 
void LineBreak_Pre_Test::setUp()
{
	m_pTexts=new vector<string>;
	m_pTexts->push_back("This is a magic book.");
	m_pLineBreak=new LineBreak_Pre(m_pTexts,15);
} 
void LineBreak_Pre_Test::tearDown() 
{ 
	delete m_pTexts;
	delete m_pLineBreak;
} 

void LineBreak_Pre_Test::testCheck1()
{
  // Set up
  bool check=false;
  // Process
  check=m_pLineBreak->check(1);
  // Check
  CPPUNIT_ASSERT_EQUAL( check,false );
}

void LineBreak_Pre_Test::testCheck2()
{
  // Set up
  bool check=false;
  // Process
  check=m_pLineBreak->check(5);
  // Check
  CPPUNIT_ASSERT_EQUAL( check,true );
}

void LineBreak_Pre_Test::testSetWidth1()
{
  // Set up
  int check;
  string result;
  string cmp("This is a magic");
  // Process
  m_pLineBreak->setWidth(14);
  result=(*m_pTexts)[0];
  check=result.compare(cmp);
  // Check
  CPPUNIT_ASSERT_EQUAL( check,0 );
}

void LineBreak_Pre_Test::testSetWidth2()
{
  // Set up
  int check;
  string result;
  string cmp("This is a ");
  // Process
  m_pLineBreak->setWidth(11);
  result=(*m_pTexts)[0];
  check=result.compare(cmp);
  // Check
  CPPUNIT_ASSERT_EQUAL( check,0 );
}

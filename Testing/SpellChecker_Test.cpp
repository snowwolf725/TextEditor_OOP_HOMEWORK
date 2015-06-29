#include "SpellChecker_Test.h"
#include <string>
using namespace std;
// Registers the fixture into the 'registry' 
CPPUNIT_TEST_SUITE_REGISTRATION( SpellChecker_Test ); 
void SpellChecker_Test::setUp()
{
	m_pDisplay=new Display_Mock();
	m_pState=new SpellChecker(m_pDisplay);
} 
void SpellChecker_Test::tearDown() 
{ 
	delete m_pState; 
	delete m_pDisplay;
} 
void SpellChecker_Test::testLoadDict1() 
{
  // Set up
  bool isload=false;
  // Process
  isload=m_pState->loadDict("foo.txt");
  // Check
  CPPUNIT_ASSERT_EQUAL( isload,false );
}

void SpellChecker_Test::testLoadDict2() 
{
  // Set up
  bool isload=false;
  // Process
  isload=m_pState->loadDict("dictionary.txt");
  // Check
  CPPUNIT_ASSERT_EQUAL( isload,true );
}

void SpellChecker_Test::testSpellChecker1() 
{
  // Set up
  bool isfind=false;
  vector<string> m_pTexts;
  m_pTexts.push_back("This is a book.");
  m_pState->m_pTexts=&m_pTexts;
  m_pState->loadDict("dictionary2.txt");
  // Process
  isfind=m_pState->spellCheck(false);
  // Check
  CPPUNIT_ASSERT_EQUAL( isfind,false );
}

void SpellChecker_Test::testSpellChecker2() 
{
  // Set up
  bool isfind=false;
  vector<string> m_pTexts;
  m_pTexts.push_back("This is a boak.");
  m_pState->m_pTexts=&m_pTexts;
  m_pState->loadDict("dictionary2.txt");
  // Process
  isfind=m_pState->spellCheck(false);
  // Check
  CPPUNIT_ASSERT_EQUAL( isfind,true );
}

void SpellChecker_Test::testFindSugges1()
{
  // Set up
  string errorword("ffffffff");
  string cmp;
  string result;
  m_pState->loadDict("dictionary2.txt");
  // Process
  result=m_pState->findsugges(errorword);
  // Check
  CPPUNIT_ASSERT_EQUAL( result.c_str(),cmp.c_str() );
}

void SpellChecker_Test::testFindSugges2()
{
  // Set up
  int ismatch=-1;
  string errorword("messege");
  string cmp("message");
  string result;
  m_pState->loadDict("dictionary2.txt");
  // Process
  result=m_pState->findsugges(errorword);
  ismatch=result.compare(cmp);
  // Check
  CPPUNIT_ASSERT_EQUAL( ismatch,0 );
}

void SpellChecker_Test::testFindSugges3()
{
  // Set up
  int ismatch=-1;
  string errorword("tastef");
  string cmp("tasted,tasteful,tastefully,taster,tastes");
  string result;
  m_pState->loadDict("dictionary2.txt");
  // Process
  result=m_pState->findsugges(errorword);
  ismatch=result.compare(cmp);
  // Check
  CPPUNIT_ASSERT_EQUAL( ismatch,0 );
}

#include "TextLocationMap_Test.h"
#include <string>
using namespace std;
// Registers the fixture into the 'registry' 
CPPUNIT_TEST_SUITE_REGISTRATION( TextLocationMap_Test ); 
void TextLocationMap_Test::setUp() {tlocmap=new TextLocationMap_Imp();} 
void TextLocationMap_Test::tearDown() { delete tlocmap; } 
void TextLocationMap_Test::testGetLocationSet() 
{
  // Set up
  vector<Location> locs;
  string words("test");
  TextLocationMap::LocationSet* result;
  locs.push_back(Location(3,3));
  tlocmap->add(words,locs);
  result=tlocmap->getLocationSet(string("test"));
  // Process
  // Check
	CPPUNIT_ASSERT( result!=NULL);
}

void TextLocationMap_Test::testGetLocationSet2() 
{
  // Set up
  vector<Location> locs;
  string words("testfff");
  TextLocationMap::LocationSet* result;
  locs.push_back(Location(3,3));
  tlocmap->add(words,locs);
  result=tlocmap->getLocationSet(string("test"));
  // Process
  // Check
	CPPUNIT_ASSERT( result==NULL);
}

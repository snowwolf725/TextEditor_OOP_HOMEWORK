#include "TextLocationMapBuilderTest.h"
#include <string>
using namespace std;
// Registers the fixture into the 'registry' 
CPPUNIT_TEST_SUITE_REGISTRATION( TextLocationMapBuilderTest ); 
void TextLocationMapBuilderTest::setUp() 
{
	tlocmap_builder=new TextLocationMapBuilder_Imp();
	tlocmap=new TextLocationMap_Mock();
} 
void TextLocationMapBuilderTest::tearDown() 
{ 
	delete tlocmap_builder;
	delete tlocmap;
} 
void TextLocationMapBuilderTest::testBuild() 
{
	// Set up
	vector<string>	*m_pTexts=new vector<string>;
	TextLocationMap_Mock *m_pLocationMap=new TextLocationMap_Mock();
	m_pTexts->push_back(string("test1 test2"));
	TextLocationMapBuilder *builder=new TextLocationMapBuilder_Imp();
	TextLocationMap_Mock::LocationSet* test;
	m_pLocationMap =(TextLocationMap_Mock *) builder->build( m_pTexts );
	test=tlocmap->getLocationSet(string("test2")); 
	// Process
	// Check
	CPPUNIT_ASSERT( test==NULL);
}

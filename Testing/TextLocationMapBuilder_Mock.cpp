#include "TextLocationMapBuilder_Mock.h" // class's header file
#include <iostream>
#include <algorithm>
using namespace std;

const string TextLocationMapBuilder_Mock::filt_elems( "\",.;:!?)(\\/\0x0D\n" );

// class constructor
TextLocationMapBuilder_Mock::TextLocationMapBuilder_Mock()
{
}

// class destructor
TextLocationMapBuilder_Mock::~TextLocationMapBuilder_Mock()
{
}

TextLocationMap*
TextLocationMapBuilder_Mock::
build(vector<string>* lines_of_text)
{
    vector<string> words;
    vector<Location> locs;

    // step 7 , build the entire product
	return build_location_map( &words, &locs );
}

void
TextLocationMapBuilder_Mock::
separate_words(vector<string>* lines_of_text, vector<string>* words, vector<Location>* locs )
{
}

void TextLocationMapBuilder_Mock::filter_text(vector<string>* words)
{
}

void TextLocationMapBuilder_Mock::suffix_text(vector<string>* words)
{
}

void TextLocationMapBuilder_Mock::strip_cap(vector<string>* words)
{
}

void TextLocationMapBuilder_Mock::exclude_text(vector<string>* words )
{
}

void
TextLocationMapBuilder_Mock::
sort_text(vector<string>* words, vector<Location>* locs)
{
}

TextLocationMap*
TextLocationMapBuilder_Mock::
build_location_map(vector<string>* words, vector<Location>* locs)
{
    /* «Ø¥ß TextLocationMap */
    TextLocationMap *map = new TextLocationMap_Imp();

    return map;
}

void TextLocationMapBuilder_Mock::loadExclude(vector<string>* lines_of_text)
{
}

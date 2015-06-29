#include "TextLocationMap_Mock.h" // class's header file

// class constructor
TextLocationMap_Mock::TextLocationMap_Mock()
{
    _words = new vector<string>;
    _locs = new vector< LocationSet >;
}

// class destructor
TextLocationMap_Mock::~TextLocationMap_Mock()
{
    delete _words;
    delete _locs;
}

void TextLocationMap_Mock::add(string words, vector<Location> locs)
{
    _words->push_back(words);
    _locs->push_back(locs);
}

TextLocationMap_Mock::LocationSet*
TextLocationMap_Mock::
getLocationSet(string word)
{
	return NULL;
}

string TextLocationMap_Mock::dump() {
	return NULL;
}

vector<string>* TextLocationMap_Mock::getWord()
{
	return _words;
}

vector<LocationSet>* TextLocationMap_Mock::getLocations()
{
	return _locs;
}

TextLocationMap_Mock::ErrorSet*
TextLocationMap_Mock::
getErrorSet(vector<string> *m_pDict)
{
	TextLocationMap_Mock::ErrorSet *error_set=new TextLocationMap_Mock::ErrorSet;
	return error_set;
}


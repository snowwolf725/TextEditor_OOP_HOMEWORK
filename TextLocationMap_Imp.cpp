#include "TextLocationMap_Imp.h" // class's header file
#include <iostream>

// class constructor
TextLocationMap_Imp::TextLocationMap_Imp()
{
    _words = new vector<string>;
    _locs = new vector< LocationSet >;
}

// class destructor
TextLocationMap_Imp::~TextLocationMap_Imp()
{
    delete _words;
    delete _locs;
}

void TextLocationMap_Imp::add(string words, vector<Location> locs)
{
    _words->push_back(words);
    _locs->push_back(locs);
}

TextLocationMap_Imp::LocationSet*
TextLocationMap_Imp::
getLocationSet(string word)
{
	if(word.find('*',0)!=string::npos)
	{
		Query myquery;
		for(unsigned int i=0;i<_words->size();i++)
			if(myquery.fuzzyQuery(word,(*_words)[i]))
			return &(*_locs)[i];
	}
	else
	{
		// case insensitive
	   	string caps("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
		string::size_type pos = 0;
		while( (pos = word.find_first_of(caps, pos)) != string::npos )
			word[pos] = tolower( word[pos] );
		
		for(unsigned int i=0;i<_words->size();i++)
			if( (*_words)[i] == word)
			return &(*_locs)[i];
	}
	
	return NULL;
}

TextLocationMap_Imp::ErrorSet*
TextLocationMap_Imp::
getErrorSet(vector<string> *m_pDict)
{
	TextLocationMap_Imp::ErrorSet *error_set=new TextLocationMap_Imp::ErrorSet;
	// case insensitive
	for(unsigned int i=0;i<_words->size();i++)
	{
		pair<string,LocationSet> error_word;
		bool isfind=false;
		//error_word.first=
		for(unsigned int j=0;j<m_pDict->size();j++)
		{
			string word=(*m_pDict)[j];
			if( (*_words)[i] == word)
			{
				isfind=true;
				break;
			}
		}
		if(isfind==false)
		{
			error_word.first=(*_words)[i];
			error_word.second=(*_locs)[i];
			error_set->push_back(error_word);
		}
	}
	return error_set;
}

string TextLocationMap_Imp::dump() {
    string line = "";
    for(unsigned int i=0;i<_words->size();i++) {
        line += (*_words)[i] + " (";
        LocationSet *ls = &(*_locs)[i];
        for(unsigned int j=0;j<ls->size();j++) {
            if( j < ls->size()-1 )
                line += (*ls)[j].toString() + ", ";
            else
                line += (*ls)[j].toString();
        }
        line = line + ")" + "\n";
    }  
    return line;
}

vector<string>* TextLocationMap_Imp::getWord()
{
	return _words;
}

vector<LocationSet>* TextLocationMap_Imp::getLocations()
{
	return _locs;
}

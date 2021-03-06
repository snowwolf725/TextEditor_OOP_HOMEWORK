// Class automatically generated by Dev-C++ New Class wizard

#ifndef TEXTLOCATIONMAP_H
#define TEXTLOCATIONMAP_H

#include <vector>
#include <string>
#include <utility>
#include "Location.h"

using namespace std;

class TextLocationMap
{
public:
	// class constructor
	TextLocationMap(){}
	// class destructor
	virtual ~TextLocationMap(){}
	typedef vector<Location> LocationSet;
	typedef vector<pair<string,LocationSet> > ErrorSet;
	virtual void add(string words, vector<Location> locs)=0;
	virtual string dump()=0;
	virtual vector<string>* getWord()=0;
	virtual vector<LocationSet>* getLocations()=0;
	virtual ErrorSet* getErrorSet(vector<string> *m_pDict)=0;
	virtual LocationSet* getLocationSet(string word)=0;
};

#endif // TEXTLOCATIONMAP_H

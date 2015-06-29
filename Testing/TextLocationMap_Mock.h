#ifndef _TEXTLOCATIONMAP_MOCK_H_
#define _TEXTLOCATIONMAP_MOCK_H_

#include <vector>
#include <string>
#include "Location_Mock.h"
#include "../TextLocationMap.h"

using namespace std;
typedef vector<Location> LocationSet;
typedef vector<pair<string,LocationSet> > ErrorSet;

class TextLocationMap_Mock : public TextLocationMap
{
public:
	void add(string words, vector<Location> locs);
	string dump();
	LocationSet* getLocationSet(string word);
	vector<string>* getWord();
	vector<LocationSet>* getLocations();
	ErrorSet* getErrorSet(vector<string> *m_pDict);
public:
	// class constructor
	TextLocationMap_Mock();
	// class destructor
	~TextLocationMap_Mock();
private:
    vector<string>* _words;
    vector<LocationSet> *_locs;
};

#endif //_TEXTLOCATIONMAP_MOCK_H_

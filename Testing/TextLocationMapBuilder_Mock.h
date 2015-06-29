// Class automatically generated by Dev-C++ New Class wizard

#ifndef TEXTLOCATIONMAPBUILDER_MOCK_H
#define TEXTLOCATIONMAPBUILDER_MOCK_H

#include <vector>
#include <string>
#include "../Location.h"
#include "../TextLocationMapBuilder.h"
#include "../TextLocationMap.h"

using namespace std;

class TextLocationMapBuilder_Mock : public TextLocationMapBuilder
{
public:
	static const string filt_elems;
	TextLocationMap* build(vector<string>* lines_of_text);
	void TextLocationMapBuilder_Mock::loadExclude(vector<string>* lines_of_text);
public:
	// class constructor
	TextLocationMapBuilder_Mock();
	// class destructor
	~TextLocationMapBuilder_Mock();
private:
	void separate_words(vector<string>* lines_of_text, vector<string>* words, vector<Location>* locs);
	void filter_text(vector<string>* words);
	void suffix_text(vector<string>* words);
	void strip_cap(vector<string>* words);
	void sort_text(vector<string>* words, vector<Location>* locs);
	void exclude_text(vector<string>* words );
	TextLocationMap* build_location_map(vector<string>* words, vector<Location>* locs);
	vector<string> exclude_words;
};

#endif // TEXTLOCATIONMAPBUILDER_MOCK_H
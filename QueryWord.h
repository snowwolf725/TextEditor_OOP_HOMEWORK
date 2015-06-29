#ifndef _QUERY_WORD_H_
#define _QUERY_WORD_H_
#include <string>
#include <vector>
#include "Tokener.h"
#include "TextLocationMap_Imp.h"
#include "TextLocationMapBuilder_Imp.h"

using namespace std;

class QueryWord
{
public:
	QueryWord(){};//for easy to test my code
	QueryWord(string qstr,vector<string> *m_pTexts);
	~QueryWord();
	bool fuzzyQuery(string qstr,string findstr);
	vector<int> getAns();
private:
	void singleQuery(string qstr,vector<string> *m_pTexts);
	void fuzzyQuery(string qstr,vector<string> *m_pTexts);
	vector<int> find_loc;
};

#endif //_QUERY_WORD_H_

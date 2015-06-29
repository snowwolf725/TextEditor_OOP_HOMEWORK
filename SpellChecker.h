#ifndef _SPELLCHECKER_H_
#define _SPELLCHECKER_H_

#include <fstream>
#include <string>
#include <vector>
#include "Display.h"
#include <sstream>
#include "TextLocationMapBuilder_Imp.h"
using namespace std;

class SpellChecker
{
public:
	SpellChecker(Display *d);
	~SpellChecker();
	bool loadDict(string dictname);
	bool spellCheck(bool sugges);
	void prompt(string msg);
	void alertError(string msg);
	void setTexts(vector<string> *t);
	vector<string> *getDict();
	void setDict(vector<string> *dict);
private:
	friend class SpellChecker_Test;	//esay for test
	void release();
	string findsugges(string word);
	vector<string> *m_pTexts;
	vector<string> *m_pDict;
	Display *m_pDisplay;
	bool _dictload;
};

#endif //_SPELLCHECKER_H_

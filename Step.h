#ifndef _STEP_H_
#define _STEP_H_

#include "Cursor.h"
#include "SpellChecker.h"
#include "Text.h"
#include <string>
#include <vector>

using namespace std;

class Step
{
public:
	Step(Cursor *c,Text *t,SpellChecker *s);
	~Step();
	void saveState();
	void loadState();
	vector<string> getContext();
private:
	void saveCursor();
	void loadCursor();
	void saveContext();
	void loadContext();
	void saveDict();
	void loadDict();
	void saveExWords();
	void loadExWords();
	void saveWidth();
	void loadWidth();
	void saveMode();
	void loadMode();
	void saveFileState();
	void loadFileState();
	//resource
	Cursor *m_pCursor;
	Text *m_pText;
	SpellChecker *m_pSpellChecker;
	//Cursor
	int _coursor_x;
	int _coursor_y;
	//Text state
	int _mode;
	int _width;
	int _fileload;
	//Context
	vector<string> m_pTexts;
	vector<string> m_pDict;
	vector<string> m_exWords;
};

#endif //_STEP_H_

#include "Step.h"
#include <iostream>

Step::Step(Cursor *c,Text *t,SpellChecker *s)
{
	m_pCursor=c;
	m_pText=t;
	m_pSpellChecker=s;
}

Step::~Step()
{
	
}

void Step::saveState()
{
	saveCursor();
	saveContext();
//	saveDict();
//	saveExWords();
	saveWidth();
	saveMode();
	saveFileState();
}

void Step::loadState()
{
	loadCursor();
	loadContext();
//	loadDict();
//	loadExWords();
	loadWidth();
	loadMode();
	loadFileState();
}

void Step::saveCursor()
{
	_coursor_x=m_pCursor->getX();
	_coursor_y=m_pCursor->getY();
}

void Step::loadCursor()
{
	m_pCursor->setX(_coursor_x);
	m_pCursor->setY(_coursor_y);
}

vector<string> Step::getContext()
{
	vector<string> context;
	if(m_pText->getTexts()!=NULL)
	{
		context=*(m_pText->getTexts());
	}
	return context;
}

void Step::saveContext()
{
	if(m_pText->getTexts()!=NULL)
		m_pTexts=*(m_pText->getTexts());
}

void Step::loadContext()
{
	m_pText->setTexts(&m_pTexts);
}

void Step::saveDict()
{
	if(m_pSpellChecker->getDict()!=NULL)
		m_pDict=*(m_pSpellChecker->getDict());
}

void Step::loadDict()
{
	m_pSpellChecker->setDict(&m_pDict);
}

void Step::saveExWords()
{
	if(m_pText->getExWords()!=NULL)
		m_exWords=*(m_pText->getExWords());
}

void Step::loadExWords()
{
	m_pText->setExWords(&m_exWords);
}

void Step::saveWidth()
{
	_width=m_pText->getWidth();
}

void Step::loadWidth()
{
	m_pText->setWidth(_width);
}

void Step::saveMode()
{
	_width=m_pText->getMode();
}

void Step::loadMode()
{
	m_pText->setMode(_mode);
}

void Step::saveFileState()
{
	_fileload=m_pText->getFileState();
}

void Step::loadFileState()
{
	m_pText->setFileState(_fileload);
}

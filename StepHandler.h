#ifndef _STEPHANDLER_H_
#define _STEPHANDLER_H_

#include "Cursor.h"
#include "SpellChecker.h"
#include "Text.h"
#include "Step.h"
#include <stack>

class StepHandler
{
public:
	static StepHandler *getInstance();
	~StepHandler();
	void saveStep();
	void loadRedoStack();
	void loadUndoStack();
	void clearUndoStack();
	void clearRedoStack();
	void setText(Text *text);
	void setChecker(SpellChecker *sc);
	void setCursor(Cursor *c);
private:
	friend class GUI_DialogMaker;
	Step getCurrentStep();
	static StepHandler *po;
	int redo;
	int undo;
	StepHandler();
	Step *m_pStep;
	stack<Step> redoStack;
	stack<Step> undoStack;
	//resource
	Cursor *m_pCursor;
	Text *m_pText;
	SpellChecker *m_pSpellChecker;
};

#endif //_STEPHANDLER_H_

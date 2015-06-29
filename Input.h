#ifndef INPUT_H_
#define INPUT_H_


#include "Text_Imp.h"
#include "Cursor_Imp.h"
#include "Tokener.h"
#include "SpellChecker.h"
#include "LineBreak_Div.h"
#include "LineBreak_Pre.h"
#include "StateMgr.h"
#include "GUI_Interface.h"
#include "WrongNumberOfArgumentsException.h"
#include "InvalidArgumentException.h"
#include "InvalidLocationException.h"
#include <sstream>
#include <string>
using namespace std;

class Text;
class Cursor;

class Input
{
public:
	virtual ~Input();
	void processInput();
	void setText(Text *t);
	void setCursor(Cursor *c);
	void setChecker(SpellChecker *s);
	void setStateMgr(StateMgr *s);
	static Input *getInstance();
	void dispatchCommand(string cmd, string arg);
private:
	Input();
	static Input *m_pInput;
	bool argCheck(int input,int ck1,int ck2);
	string lastCmd;
	string lastArg;
	Text *m_pText;
	Cursor *m_pCursor;
	SpellChecker *m_pSpellChecker;
	StateMgr *m_pState;
};

#endif /*INPUT_H_*/

#ifndef _CURSOR_Imp_H_
#define _CURSOR_Imp_H_

#include "Cursor.h"
using namespace std;

class Display;

class Cursor_Imp : public Cursor
{
public:
	void setPage(int newpage);
	int GetPage();
	void setTotolLine(int newTline);
	void setTotolPage(int newTpage);
	int GetTotolLine();
	int GetTotolPage();
	int addPageno();
	int subPageno();
	void setDisplay(Display *d);
	void inputPrompt();
	void gotoHome();
	void gotoEnd();
	void setPos(int newYpos,int newXpos);
public:
	Cursor_Imp();
	static Cursor_Imp *getInstance();
	virtual ~Cursor_Imp();
private:
	static Cursor_Imp *po;
	int page;
	int Tline;
	int Tpage;
	Display *m_pDisplay;
};

#endif //_CURSOR_Imp_H_

#ifndef _CURSOR_MOCK_H_
#define _CURSOR_MOCK_H_

#include "../Cursor.h"
using namespace std;

class Display;

class Cursor_Mock : public Cursor
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
	Cursor_Mock();
	virtual ~Cursor_Mock();
private:
	 int page;
	 int Tline;
	 int Tpage;
	 Display *m_pDisplay;
};

#endif //_CURSOR_MOCK_H_

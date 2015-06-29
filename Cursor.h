#ifndef _CURSOR_H_
#define _CURSOR_H_

#include "Location.h"
#include "Display.h"
#include "StateMgr.h"
using namespace std;

class Display;

class Cursor : public Location
{
public:
	Cursor(){}
	virtual ~Cursor(){}
	virtual void setPage(int newpage)=0;
	virtual int GetPage()=0;
	virtual void setTotolLine(int newTline)=0;
	virtual void setTotolPage(int newTpage)=0;
	virtual int GetTotolLine()=0;
	virtual int GetTotolPage()=0;
	virtual int addPageno()=0;
	virtual int subPageno()=0;
	virtual void setDisplay(Display *d)=0;
	virtual void inputPrompt()=0;
	virtual void gotoHome()=0;
	virtual void gotoEnd()=0;
	virtual void setPos(int newYpos,int newXpos)=0;
};

#endif //_CURSOR_H_

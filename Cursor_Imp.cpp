#include "Cursor_Imp.h"
#include "Display.h"

Cursor_Imp::Cursor_Imp()
{
}

Cursor_Imp::~Cursor_Imp()
{
}

void Cursor_Imp::setDisplay(Display *d)
{
	m_pDisplay = d;
}

void Cursor_Imp::inputPrompt()
{
	if(StateMgr::getGUIState()==true)
		m_pDisplay->showState(this->toString());
	else
		m_pDisplay->drawPrompt(this->toString());
}

void Cursor_Imp::setPage(int newpage)
{
	page=newpage;
}

int Cursor_Imp::GetPage()
{
	page=_y/20;
	return page;
}

void Cursor_Imp::setTotolLine(int newTline)
{
	Tline=newTline;
}

void Cursor_Imp::setTotolPage(int newTpage)
{
	Tpage=newTpage;
}

int Cursor_Imp::GetTotolLine()
{
	return Tline;
}

int Cursor_Imp::GetTotolPage()
{
	return Tpage;
}

int Cursor_Imp::addPageno()
{
	if((_y+20)>Tline)
	{
		_y=Tline;
		return -1;
	}
	else 
	{
		_y=_y+20;
		return 0;
	}
	return -1;
}

int Cursor_Imp::subPageno()
{
	if((_y-20)<0)
	{
		_y=0;
		return -1;
	}
	else 
	{
		_y=_y-20;
		return 0;
	}
	return -1;
}

void Cursor_Imp::gotoHome()
{
	setPos(0,0);
	setPage(0);
}

void Cursor_Imp::gotoEnd()
{
	setPos(GetTotolLine(),0);
	setPage(GetTotolLine()/20);
}

void Cursor_Imp::setPos(int newYpos,int newXpos)
{
	setX(newXpos);
	setY(newYpos);
}

Cursor_Imp *Cursor_Imp::po=NULL;

Cursor_Imp *Cursor_Imp::getInstance()
{
	if(po==NULL)po=new Cursor_Imp();
	return po;
}

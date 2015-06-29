#include "Cursor_Mock.h"
#include "../Display.h"

Cursor_Mock::Cursor_Mock()
{
}

Cursor_Mock::~Cursor_Mock()
{
}

void Cursor_Mock::setDisplay(Display *d)
{
	m_pDisplay = d;
}

void Cursor_Mock::inputPrompt()
{
	m_pDisplay->drawPrompt(this->toString());
}

void Cursor_Mock::setPage(int newpage)
{
	page=newpage;
}

int Cursor_Mock::GetPage()
{
	page=_y/20;
	return page;
}

void Cursor_Mock::setTotolLine(int newTline)
{
	Tline=newTline;
}

void Cursor_Mock::setTotolPage(int newTpage)
{
	Tpage=newTpage;
}

int Cursor_Mock::GetTotolLine()
{
	return Tline;
}

int Cursor_Mock::GetTotolPage()
{
	return Tpage;
}

int Cursor_Mock::addPageno()
{
	return -1;
}

int Cursor_Mock::subPageno()
{
	return -1;
}

void Cursor_Mock::gotoHome()
{
}

void Cursor_Mock::gotoEnd()
{
}

void Cursor_Mock::setPos(int newYpos,int newXpos)
{
}

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <string>
//#include "GUI_Interface.h"
using namespace std;

class GUI_Interface;

class Display
{
public:
	Display(){}
	virtual ~Display(){}
	virtual void drawText(string line)=0;
	virtual void drawContext(string context)=0;
	virtual void drawPrompt(string prom)=0;
	virtual void setGUI(GUI_Interface *g)=0;
	virtual void showState(string state)=0;
};

#endif /*DISPLAY_H_*/

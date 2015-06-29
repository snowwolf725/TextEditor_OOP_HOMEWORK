#ifndef DISPLAY_IMP_H_
#define DISPLAY_IMP_H_

#include <string>
#include "Display.h"
#include "GUI_Interface.h"
#include "GUI_InfoDialog.h"
#include "StateMgr.h"
using namespace std;

class Display_Imp :public Display
{
public:
	void drawText(string line);
	void drawContext(string context);
	void drawPrompt(string prom);
	void setGUI(GUI_Interface *g);
	void showState(string state);
public:
	Display_Imp();
	virtual ~Display_Imp();
private:
	GUI_Interface *m_pGUI;
};

#endif /*DISPLAY_IMP_H_*/

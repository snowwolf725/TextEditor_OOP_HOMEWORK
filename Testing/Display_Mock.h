#ifndef DISPLAY_MOCK_H_
#define DISPLAY_MOCK_H_

#include <string>
#include "../Display.h"
#include "../GUI_Interface.h"
using namespace std;

class Display_Mock :public Display
{
public:
	void drawText(string line);
	void drawContext(string context);
	void drawPrompt(string prom);
	void setGUI(GUI_Interface *g);
	void showState(string state);
public:
	Display_Mock();
	virtual ~Display_Mock();
};

#endif /*DISPLAY_MOCK_H_*/

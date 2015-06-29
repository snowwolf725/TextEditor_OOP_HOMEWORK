#include <iostream>
#include <gtk/gtk.h>
#include "Display_Imp.h"

using namespace std;

Display_Imp::Display_Imp() 
{
}

Display_Imp::~Display_Imp()
{
}

void Display_Imp::drawText(string line)
{
	if(StateMgr::getGUIState()==true)
	{
	//	m_pGUI->setText(line);
		GUI_InfoDialog ginfo;
		ginfo.showGUI(line);
	}
	cout << line << endl;
}

void Display_Imp::drawContext(string context)
{
	m_pGUI->setText(context);
}

void Display_Imp::drawPrompt(string prom)
{
	static const string PROMPT = " >";
	cout << prom << PROMPT;
}

void Display_Imp::showState(string state)
{
	if(StateMgr::getGUIState()==true)	
	{
		if(StateMgr::getModeState()==0)
			m_pGUI->setStateBar(state+"  Character-based mode");
		else m_pGUI->setStateBar(state+"  Word-based mode");
	}
}

void Display_Imp::setGUI(GUI_Interface *g)
{
	m_pGUI=g;
}

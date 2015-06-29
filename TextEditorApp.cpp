#include "TextEditorApp.h"

TextEditorApp::
TextEditorApp(Text *t, Display *d, Input *i, Cursor *c,GUI_Interface *g)
: m_pText(t), m_pDisplay(d), m_pInput(i), m_pCursor(c), m_pGUI(g)
{
    m_pInput->setText(m_pText);
    m_pInput->setCursor(m_pCursor);
    m_pInput->setCursor(m_pCursor);
    m_pSpellChecker=new SpellChecker(m_pDisplay);
    m_pInput->setChecker(m_pSpellChecker);
    m_pText->setDisplay(m_pDisplay);
    m_pText->setCursor(m_pCursor);
    m_pCursor->setDisplay(m_pDisplay);
    m_pState=StateMgr::getInstance();
    m_pInput->setStateMgr(m_pState);
 //   m_pDisplay->setGUI(m_pGUI);
 
 	//register resource
 	StepHandler *m_pHandler=StepHandler::getInstance();
 	m_pHandler->setText(m_pText);
 	m_pHandler->setChecker(m_pSpellChecker);
 	m_pHandler->setCursor(m_pCursor);
 }
 
TextEditorApp::~TextEditorApp()
{
	delete m_pText;
	delete m_pDisplay;
	delete m_pInput;
	delete m_pCursor;
	delete m_pGUI;
	delete m_pSpellChecker;
	delete m_pState;
}

void TextEditorApp::run()
{
    while(1) {
    	if(m_pState->getGUIState()==true)
    	m_pGUI->show();
    	// Command Line prompt
		m_pCursor->inputPrompt();

		// process external message
		m_pInput->processInput();
	}
}

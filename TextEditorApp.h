#ifndef TEXTEDITORAPP_H_
#define TEXTEDITORAPP_H_

#include "Text_Imp.h"
#include "Display_Imp.h"
#include "Input.h"
#include "Cursor_Imp.h"
#include "SpellChecker.h"
#include "GUI_Interface.h"
#include "StateMgr.h"
#include "StepHandler.h"

class TextEditorApp {
public:
     TextEditorApp(Text *t, Display *d, Input *i, Cursor *c,GUI_Interface *g);
     ~TextEditorApp();
     void run();
private:
     Text *m_pText;
     Display *m_pDisplay;
     Input *m_pInput;
     Cursor *m_pCursor;
     SpellChecker *m_pSpellChecker;
     GUI_Interface *m_pGUI;
     StateMgr *m_pState;
};

#endif /*TEXTEDITORAPP_H_*/

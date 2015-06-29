#ifndef TEXT_IMP_H_
#define TEXT_IMP_H_

#include <string>
#include <vector>
#include "Text.h"
#include "TextLocationMap_Imp.h"
#include "Display.h"
#include "Cursor_Imp.h"
#include "Multiquery.h"
#include "TextLocationMapBuilder_Imp.h"
#include "Tokener.h"
#include "InvalidArgumentException.h"
#include "InvalidLocationException.h"
#include <algorithm>

using namespace std;

class Text_Imp : public Text
{
public:
	void newFile();
	void readFile(string filename);
	void saveFile(string filename);
	void exclude(string filename);
	void insertfile(string filename);
	void query(Tokener tok,string m_query);
	void queryWord(Tokener tok,string m_query);
	void search(string arg);
	void search_Char(string arg);
	void search_SingleChar(string arg);
	void search_FuzzyChar(string arg);
	void map();
	void display(string arg);
	void displayPLine();
	void displayPPage();
	void displayNLine();
	void displayNPage();
	int safeCheck(bool showmsg);
	int  setPos(int newYpos,int newXpos);
	int  setPos_Char(int newYpos,int newXpos);
	void insert(string arg,int x,int y);
	void insert_Char(string arg,int x,int y);
	void delWord(int x,int y);
	void delChar(int x,int y);
	bool copyWord(int x,int y);
	bool copyChar(int x,int y);
	bool cutWord(int x,int y);
	bool cutChar(int x,int y);
	bool pasteWord(int x,int y);
	bool pasteChar(int x,int y);
	bool modifyWord(string arg,int x,int y);
	bool modifyChar(string arg,int x,int y);
	bool replaceString(string arg1,string arg2);
	bool replaceWord(string arg1,string arg2);
	void deleteRow(int row);
	void eli_empty();
	void eli_head();
	void eli_tail();
	void compact();
	vector<string> *getTexts();
	void setTexts(vector<string> *Texts);
	vector<string> *getExWords();
	void setExWords(vector<string> *exWords);
	void chgLineBreakState(string newstate);
	string getLineBreakState();
	void chgLineWidth(int width);
	int getLineWidth();
	void fixBoundary();
	void renewContext();
public:
    Text_Imp();
    virtual ~Text_Imp();

	void setDisplay(Display *v);
	void setCursor(Cursor *c);
	void alertError(string msg);
	void prompt(string msg);
	void updateContext(string context);
	int getWidth();
	void setWidth(int width);
	int getMode();
	void setMode(int m);
	int getFileState();
	void setFileState(int fload);
private:
	void release();
	void releaseOther();
	string displayLine(int lineno,int type=0);
	void displayPage();
	int colOfLine(int lineno);
	int colOfLine_Char(int lineno);
	int toPhyLoc(int xpos,int ypos);
	int toLogLoc(int xpos,int ypos);
	Location tagWord(int xpos,int ypos);
private:
	Display *m_pDisplay;
	Cursor *m_pCursor;
	vector<string> *m_pTexts;
	vector<string> *m_exWords;
	bool fileload;
	string copy_word;
	int mode;
	string _linestate;
	int _width;
};

/***************************************************************************/
/* Fnction Object for output to display */
class OutputToDisplay {
public:
    OutputToDisplay(Display *display): _display(display) {}
    ~OutputToDisplay() {}
    void operator()(string line) {  _display->drawText( line );  }
private:
    OutputToDisplay() {}
    Display *_display;    
};

#endif /*TEXT_IMP_H_*/

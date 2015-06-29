#ifndef TEXT_H_
#define TEXT_H_

#include <string>
#include <vector>
#include "Location.h"
#include "TextLocationMap.h"
#include "TextLocationMapBuilder.h"
#include "Display.h"
#include "Cursor.h"
#include "Tokener.h"

using namespace std;

class Text
{
public:
	Text(){}
	virtual ~Text(){}
	virtual void newFile()=0;
	virtual void readFile(string filename)=0;
	virtual void saveFile(string filename)=0;
	virtual void exclude(string filename)=0;
	virtual void insertfile(string filename)=0;
	virtual void query(Tokener tok,string m_query)=0;
	virtual void queryWord(Tokener tok,string m_query)=0;
	virtual void search(string arg)=0;
	virtual void search_Char(string target)=0;
	virtual void map()=0;
	virtual void display(string arg)=0;
	virtual void displayPLine()=0;
	virtual void displayPPage()=0;
	virtual void displayNLine()=0;
	virtual void displayNPage()=0;
	virtual int safeCheck(bool showmsg)=0;
	virtual int  setPos(int newYpos,int newXpos)=0;
	virtual int  setPos_Char(int newYpos,int newXpos)=0;
	virtual void insert(string arg,int x,int y)=0;
	virtual void insert_Char(string arg,int x,int y)=0;
	virtual void delWord(int x,int y)=0;
	virtual void delChar(int x,int y)=0;
	virtual bool copyWord(int x,int y)=0;
	virtual bool pasteWord(int x,int y)=0;
	virtual bool copyChar(int x,int y)=0;
	virtual bool pasteChar(int x,int y)=0;
	virtual bool cutWord(int x,int y)=0;
	virtual bool cutChar(int x,int y)=0;
	virtual bool modifyWord(string arg,int x,int y)=0;
	virtual bool modifyChar(string arg,int x,int y)=0;
	virtual bool replaceString(string arg1,string arg2)=0;
	virtual bool replaceWord(string arg1,string arg2)=0;
	virtual void deleteRow(int row)=0;
	virtual void setMode(int mode)=0;
	virtual int getMode()=0;
	virtual void setDisplay(Display *v)=0;
	virtual void setCursor(Cursor *c)=0;
	virtual void alertError(string msg)=0;
	virtual void prompt(string msg)=0;
	virtual void updateContext(string context)=0;
	virtual void eli_empty()=0;
	virtual void eli_head()=0;
	virtual void eli_tail()=0;
	virtual void compact()=0;
	virtual void chgLineBreakState(string newstate)=0;
	virtual string getLineBreakState()=0;
	virtual void chgLineWidth(int width)=0;
	virtual int getLineWidth()=0;
	virtual vector<string> *getTexts()=0;
	virtual void setTexts(vector<string> *Texts)=0;
	virtual vector<string> *getExWords()=0;
	virtual void setExWords(vector<string> *exWords)=0;
	virtual void fixBoundary()=0;
	virtual int getFileState()=0;
	virtual void setFileState(int fload)=0;
	virtual int getWidth()=0;
	virtual void setWidth(int width)=0;
	virtual void renewContext()=0;
};

#endif /*TEXT_H_*/

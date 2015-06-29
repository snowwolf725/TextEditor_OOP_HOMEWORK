#ifndef _LINEBREAK_DIV_H_
#define _LINEBREAK_DIV_H_

#include "LineBreak.h"
#include "Tokener.h"
#include <string>
#include <vector>

using namespace std;

class LineBreak_Div:public LineBreak
{
public:
	LineBreak_Div(vector<string> *t,int width);
	~LineBreak_Div();
	bool check(int width);
	bool setWidth(int width);
	void revert();
private:
	vector<string> *m_pTexts;
	int _width;
};

#endif //_LINEBREAK_DIV_H_

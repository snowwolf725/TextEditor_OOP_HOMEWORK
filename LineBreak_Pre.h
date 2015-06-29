#ifndef _LINEBREAK_PRE_H_
#define _LINEBREAK_PRE_H_

#include <string>
#include <vector>
#include "LineBreak.h"
#include "Tokener.h"

using namespace std;

class LineBreak_Pre:public LineBreak
{
public:
	LineBreak_Pre(vector<string> *t,int width);
	~LineBreak_Pre();
	bool check(int width);
	bool setWidth(int width);
	void revert();
private:
	vector<string> *m_pTexts;
	int _width;
};

#endif //_LINEBREAK_PRE_H_

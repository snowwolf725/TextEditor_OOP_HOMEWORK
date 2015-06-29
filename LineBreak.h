#ifndef _LINEBREAK_H_
#define _LINEBREAK_H_

#include <string>
#include <vector>

using namespace std;

class LineBreak
{
public:
	LineBreak(){}
	LineBreak(vector<string> *t,int width){}
	virtual ~LineBreak(){}
	virtual bool setWidth(int width)=0;
	virtual void revert()=0;
	virtual bool check(int width)=0;
};

#endif //_LINEBREAK_H_

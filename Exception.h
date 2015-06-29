#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <string>

using namespace std;

class Exception
{
public:
	Exception();
	~Exception();
	string getname();
protected:
	string _name;
};

#endif //_EXCEPTION_H_

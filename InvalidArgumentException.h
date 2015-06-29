#ifndef _INVALIDARGUMENTEXCEPTION_H_
#define _INVALIDARGUMENTEXCEPTION_H_

#include "Exception.h"

class InvalidArgumentException:public Exception
{
public:
	InvalidArgumentException(string arg);
	~InvalidArgumentException();
	string getarg();
private:
	string _arg;
};

#endif //_INVALIDARGUMENTEXCEPTION_H_

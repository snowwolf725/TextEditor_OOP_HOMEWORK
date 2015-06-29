#ifndef _WRONGNUMBEROFARGUMENTSEXCEPTION_H_
#define _WRONGNUMBEROFARGUMENTSEXCEPTION_H_

#include "Exception.h"

class WrongNumberOfArgumentsException : public Exception
{
public:
	WrongNumberOfArgumentsException(int arg,int limitarg1,int limitarg2);
	~WrongNumberOfArgumentsException();
	int getargc();
	int getlimitarg1();
	int getlimitarg2();
private:
	int _argc;
	int _limitarg1;
	int _limitarg2;
};

#endif //_WRONGNUMBEROFARGUMENTSEXCEPTION_H_

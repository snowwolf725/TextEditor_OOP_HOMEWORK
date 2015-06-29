#include "WrongNumberOfArgumentsException.h"

WrongNumberOfArgumentsException::WrongNumberOfArgumentsException(int arg,int limitarg1,int limitarg2)
	:_argc(arg),_limitarg1(limitarg1),_limitarg2(limitarg2)
{
	_name="WrongNumberOfArgumentsException";
}

WrongNumberOfArgumentsException::~WrongNumberOfArgumentsException()
{

}

int WrongNumberOfArgumentsException::getargc()
{
	return _argc;
}

int WrongNumberOfArgumentsException::getlimitarg1()
{
	return _limitarg1;
}

int WrongNumberOfArgumentsException::getlimitarg2()
{
	return _limitarg2;
}

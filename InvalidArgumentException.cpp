#include "InvalidArgumentException.h"

InvalidArgumentException::InvalidArgumentException(string arg):_arg(arg)
{
	_name="InvalidArgumentException";
}

InvalidArgumentException::~InvalidArgumentException()
{

}

string InvalidArgumentException::getarg()
{
	return _arg;
}

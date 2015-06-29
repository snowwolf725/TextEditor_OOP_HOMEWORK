#include "Exception.h"

Exception::Exception()
{
	_name="General Exception";
}

Exception::~Exception()
{
	
}

string Exception::getname()
{
	return _name;
}

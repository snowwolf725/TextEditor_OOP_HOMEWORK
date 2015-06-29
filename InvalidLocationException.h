#ifndef _INVALIDLOCATIONEXCEPTION_H_
#define _INVALIDLOCATIONEXCEPTION_H_

#include "Exception.h"
#include "Location.h"

class InvalidLocationException:public Exception
{
public:
	InvalidLocationException(Location loc);
	~InvalidLocationException();
	Location getLocation();
private:
	Location _loc;
};

#endif //_INVALIDLOCATIONEXCEPTION_H_

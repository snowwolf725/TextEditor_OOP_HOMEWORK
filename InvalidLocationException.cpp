#include "InvalidLocationException.h"

InvalidLocationException::InvalidLocationException(Location loc):_loc(loc)
{
	_name="InvalidLocationException";
}

InvalidLocationException::~InvalidLocationException()
{

}

Location InvalidLocationException::getLocation()
{
	return _loc;
}

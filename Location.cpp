#include <sstream>

#include "Location.h" // class's header file

// class constructor
Location::Location() : _x(-1), _y(-1)
{
}

// class constructor
Location::Location(int x, int y) : _x(x), _y(y)
{
}

// class destructor
Location::~Location(){ }

void Location::set(int x, int y) {
    _x = x;
    _y = y;
}

void Location::setX(int x)
{
    _x = x;
}

void Location::setY(int y)
{
    _y = y;
}

std::string Location::toString()
{
   	std::ostringstream oss;
   	oss << "(" << _y+1 << ", " << _x+1 << ")";
   	return oss.str();
}

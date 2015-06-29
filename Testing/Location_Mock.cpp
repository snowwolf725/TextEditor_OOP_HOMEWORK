#include <sstream>

#include "Location_Mock.h" // class's header file

// class constructor
Location_Mock::Location_Mock() : _x(-1), _y(-1)
{
}

// class constructor
Location_Mock::Location_Mock(int x, int y) : _x(x), _y(y)
{
}

// class destructor
Location_Mock::~Location_Mock(){ }

void Location_Mock::set(int x, int y) {
    _x = x;
    _y = y;
}

void Location_Mock::setX(int x)
{
    _x = x;
}

void Location_Mock::setY(int y)
{
    _y = y;
}

std::string Location_Mock::toString()
{
   	std::ostringstream oss;
   	oss << "(" << _y+1 << ", " << _x+1 << ")";
   	return oss.str();
}

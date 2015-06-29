#ifndef LOCATION_H
#define LOCATION_H

#include <string>

class Location
{
public:
	void set(int x, int y);
	void setX(int x);
	void setY(int y);
	int getX() { return _x; }
	int getY() { return _y; }
    std::string toString();
public:
	Location();
	Location(int x, int y);
	~Location();
protected:
    int _x, _y;
};

#endif // LOCATION_H

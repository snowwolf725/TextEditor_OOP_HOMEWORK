#ifndef LOCATION_MOCK_H
#define LOCATION_MOCK_H

#include "../Location.h"
#include <string>

class Location_Mock : public Location
{
public:
	void set(int x, int y);
	void setX(int x);
	void setY(int y);
	int getX() { return _x; }
	int getY() { return _y; }
    std::string toString();
public:
	Location_Mock();
	Location_Mock(int x, int y);
	~Location_Mock();
protected:
    int _x, _y;
};

#endif // LOCATION_MOCK_H

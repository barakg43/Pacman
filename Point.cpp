#include "Point.h"
#include <math.h>

// Getters
int Point::getX() const
{
	return _x;
}
int Point::getY() const
{
	return _y;
}
// Setters
void Point::initializePoint(const int x, const int y) // set x and y fields
{
	setX(x); // initialize the x field
	setY(y); // initialize the y field
}
void Point::setX(const int x)
{
	_x = x;
}
void Point::setY(const int y)
{
	_y = y;
}
bool Point::operator ==(const  Point& other) const
{
	if (_x == other._x && _y == other._y)
		return true;
	else
		return false;
}
bool Point::operator !=(const  Point& other) const
{
	return !(operator==(other));
}
ostream& operator<<(ostream& os, const Point& pos)
{
	
	os << " (" << pos._x << ',' << pos._y << ") ";
	return os;
}

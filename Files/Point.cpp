#include "Point.h"
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
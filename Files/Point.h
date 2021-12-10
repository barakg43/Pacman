#pragma once
#include <windows.h>
#include <iostream>
#include "io_utils.h"
using namespace std;
class Point
{
private:
	int _x;
	int _y;
public:



	//Constructors
	Point(int x = 0, int y = 0) : _x(x), _y(y) {} // Init line constructor
	// Getters
	int getX() const;
	int getY() const;
	// Setters
	void initializePoint(const int x, const int y);
	void setX(const int x);
	void setY(const int y);
};
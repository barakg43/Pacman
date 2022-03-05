#pragma once
#include "Point.h"
//#include "Ghost.h"
class Ghost;//ghost is included in move and move is included in ghost.

class Move
{
	
public:
	virtual void pickDirection(const Point& pacmanPosition, Ghost* ghost, int ghostNum);
};

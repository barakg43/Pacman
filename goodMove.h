#pragma once
#include "Move.h"
#include "bestMove.h"

class goodMove :public bestMove
{
	int randLoop;
	int numOfRandomMoves;
	int loopsCounter;

	enum{ RANDOM_MOVES =10, MAX_LOOPS=20};


public:
	goodMove()
	{
		/*override default of 'bestMove',because of the random in pickDirection
		we cant assume that all ghost be smartly in the same round*/
		searchDirectionAllGhost = false;

		
		randLoop = -1;
		loopsCounter = 0;
		numOfRandomMoves = 0;

	}
	void pickDirection(const Point& pacmanPosition, Ghost*ghost, int ghostNum);


};
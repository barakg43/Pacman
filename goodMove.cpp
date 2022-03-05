#include "goodMove.h"
#include "Game.h"

void goodMove::pickDirection(const Point& pacmanPosition, Ghost* ghost, int ghostNum)
{
	loopsCounter++;
	
	//every 20 loops, we choose a random loop that the ghost will pick random direction instead of following the pacman.
	if (loopsCounter == MAX_LOOPS)
	{
		
		loopsCounter = 0;
		randLoop = 1 + rand() % (MAX_LOOPS-1);//num between 1-19
	}//when we get to the random loop we choose a direction and stick with it 5 moves
	else if (randLoop == loopsCounter)
	{
		numOfRandomMoves = RANDOM_MOVES;
		Move::pickDirection(pacmanPosition, ghost + ghostNum,ghostNum);
	}//stay in the same direction for 5 moves unless the move is illegal
	else if (numOfRandomMoves > 0)
	{
		if (!Game::isValidDirection((ghost + ghostNum)->getDirection(), (ghost+ghostNum)->getPosition(), !Game::ALLOW_TUNNEL, !Game::ALLOW_STAY))
			Move::pickDirection(pacmanPosition, ghost + ghostNum,0);
		numOfRandomMoves--;
	}
	//pick a smart direction to follow the pacman
	else
	{
		bestMove::pickDirection(pacmanPosition, ghost + ghostNum,0);
	}
}







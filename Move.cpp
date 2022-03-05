#include "Move.h"
#include "Game.h"


void Move::pickDirection(const Point& pacmanPosition, Ghost* ghost, int ghostNum)
{
//	//pick direction randomly


	while (!(Game::isValidDirection(ghost->getDirection(), ghost->getPosition(), !Game::ALLOW_TUNNEL, !Game::ALLOW_STAY)))
	{

		ghost->setDirection(rand() % Game::NUM_OF_DIRECTION);
	}
	

}
#include "bestMove.h"
#include "Game.h"

void bestMove::pickDirection(const Point& pacmanPosition,Ghost* ghost, int ghostNum)
{
	
		
	if (rand()%(Game::MOVE_COUNTER_ROUNDS*2)==ghostNum)
		Move::pickDirection(pacmanPosition, ghost, 0);
	else if(!searchDirectionAllGhost|| ghostNum==0)
		getSmartDirection(pacmanPosition, ghost, searchDirectionAllGhost);


}

void bestMove::resetVisitedArry()
{


	for (int row = 0; row < GameBoard::MAX_HEIGHT; row++)
		for (int col = 0; col < GameBoard::MAX_WIDTH; col++)
		{
			markVisitedboard[row][col] = false;
		}
}

void bestMove::getSmartDirection(const Point& pacmanPosition, Ghost* ghost, bool searchDirectionAllGhost)
{
	//use bfs for the ghost chase the pacman with smart direction
	std::queue<NodePath> ShortestPathGraph;
	resetVisitedArry();
	NodePath currNode(pacmanPosition, 0);
	bool foundPaths = false;
	ShortestPathGraph.push(currNode);
	auto yPos = pacmanPosition.getY();
	auto xPos = pacmanPosition.getX();
	markVisitedboard[yPos][xPos] = true;
	for (int i = 0; i < Game::getGhostNumber(); i++)//init the helper arrays
	{
		foundAllGhostDircetions[i] = false;
		shortestPathGhosts[i] = GameBoard::MAX_HEIGHT * GameBoard::MAX_WIDTH;
	}
	while (!ShortestPathGraph.empty() && !foundPaths)
	{

		NodePath currCell = ShortestPathGraph.front();
		ShortestPathGraph.pop();
		yPos = currCell.pos.getY();
		xPos = currCell.pos.getX();
	
		if ( !markVisitedboard[yPos - 1][xPos] &&Game::isValidDirection(Game::DIRECTION::UP, currCell.pos, !Game::ALLOW_TUNNEL, !Game::ALLOW_STAY))//UP
		{
		
			setSmartDirectionsToGhosts({ xPos ,yPos -1}, ghost, Game::DIRECTION::DOWN, currCell.length);
			ShortestPathGraph.push({ { xPos ,yPos - 1 }, currCell.length + 1 });
			markVisitedboard[yPos - 1][xPos] = true;
		}
	
		if (!markVisitedboard[yPos][xPos - 1] &&Game::isValidDirection(Game::DIRECTION::LEFT, currCell.pos, !Game::ALLOW_TUNNEL, !Game::ALLOW_STAY))//LEFT
		{
			setSmartDirectionsToGhosts({ xPos - 1 ,yPos }, ghost, Game::DIRECTION::RIGHT, currCell.length);
			ShortestPathGraph.push({ { xPos - 1 ,yPos}, currCell.length + 1 });
			markVisitedboard[yPos][xPos - 1] = true;
	
		}

		if (!markVisitedboard[yPos + 1][xPos] &&Game::isValidDirection(Game::DIRECTION::DOWN, currCell.pos, !Game::ALLOW_TUNNEL, !Game::ALLOW_STAY))//DOWN
		{

			setSmartDirectionsToGhosts({ xPos ,yPos + 1 }, ghost, Game::DIRECTION::UP, currCell.length);
			ShortestPathGraph.push({ { xPos ,yPos + 1 }, currCell.length + 1 });
			markVisitedboard[yPos + 1][xPos] = true;
		
		}

		if ( !markVisitedboard[yPos][xPos + 1]&&Game::isValidDirection(Game::DIRECTION::RIGHT, currCell.pos, !Game::ALLOW_TUNNEL, !Game::ALLOW_STAY))//RIGHT
		{

			setSmartDirectionsToGhosts({ xPos + 1 ,yPos }, ghost, Game::DIRECTION::LEFT, currCell.length);
			ShortestPathGraph.push({ { xPos + 1 ,yPos }, currCell.length + 1 });
			markVisitedboard[yPos][xPos + 1] = true;

		}
		foundPaths = allGhostsFoundDirections();
		
	}

}

void bestMove::setSmartDirectionsToGhosts(const Point& virtualPacPos, Ghost* ghost, int direction,int currLenPath)
{

		for (int i = 0; i==0 ||(i < Game::getGhostNumber()&& searchDirectionAllGhost); i++)
			if (!foundAllGhostDircetions[i]&&shortestPathGhosts[i] > currLenPath && virtualPacPos == ghost[i].getPosition())
			{
				ghost[i].setDirection(direction);
				foundAllGhostDircetions[i] = true;
				shortestPathGhosts[i] = currLenPath;
			}
}

bool bestMove::allGhostsFoundDirections()
{
	bool foundAll =true;


	for (int i = 0; i == 0 || (i < Game::getGhostNumber() && searchDirectionAllGhost); i++)
			if (!foundAllGhostDircetions[i])
					foundAll = false;
	
	return foundAll;
}

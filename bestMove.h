#ifndef bestMove_h
#define bestMove_h

#include <queue>
#include "Move.h"
#include "Point.h"
#include "GameBoard.h"
#include "Game.h"
class bestMove :public Move
{

	bool markVisitedboard[GameBoard::MAX_HEIGHT][GameBoard::MAX_WIDTH];
	Point prevPosition;
	int ghostDirections[Game::MAX_GHOSTS];
	int shortestPathGhosts[Game::MAX_GHOSTS];
	bool foundAllGhostDircetions[Game::MAX_GHOSTS] ={ false };
protected:

	bool searchDirectionAllGhost = true;/*by default,search for all ghost direction by the same time*/

	class NodePath
	{
		Point pos;
		int length;
		NodePath(const Point& _pos,int len):pos(_pos),length(len){}
		friend class bestMove;
	};

private:
	bool allGhostsFoundDirections();
	void resetVisitedArry();
	void getSmartDirection(const Point& pacmanPosition, Ghost* ghost, bool searchDirectionAllGhost);
	void setSmartDirectionsToGhosts(const Point& virtualPacPos, Ghost* ghost,int direction, int currLenPath);
public:
	void pickDirection(const Point& pacmanPosition, Ghost* ghost, int ghostNum);
};
#endif // !bestMove_h
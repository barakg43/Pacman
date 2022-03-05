#include "Ghost.h"
#include "Game.h"
//#include "Point.h"
#include "GameBoard.h"
#include "bestMove.h"
#include "Move.h"
#include "goodMove.h"
// Getters
Point& Ghost::getPosition()
{
	return _position;
}
bool Ghost::getMovement() const

{
	return _isMovement;
}
int Ghost::getDirection()const
{
	return _direction;
}

// Setters

void Ghost::setPosition(const Point& pos)
{

	_position = pos;
}
void Ghost::setDirection(int dir)
{
	_direction = dir;
}
void Ghost::setIsMovement(bool value)
{
	_isMovement = value;
}
void Ghost::setMoveStrategy(char ghostLevel)
{
	delete moveStrategy;//success only if not nullptr,cannot be garbage pointer value
	if (ghostLevel == GameMenu::GHOST_TYPE::BEST_GHOST_LEVEL)//best ghost option
	{
		moveStrategy = new bestMove();
	}
	else if (ghostLevel == GameMenu::GHOST_TYPE::GOOD_GHOST_LEVEL)//good ghost option
	{
		moveStrategy = new goodMove();
	}
	else//novice ghost
		moveStrategy = new Move();


	if (moveStrategy == nullptr)
		throw Game::excepMgr.insertExcp("failed to allocate memory for moveStrategy!");

}
Move*& Ghost::getMoveStrategy()
{
	return moveStrategy;
}

//// Methods
//void Ghost::pickDirection() // Chooses the next step of each ghost randomly, depends of the walls next to it
//{
//
//	while (!(Game::isValidDirection(getDirection(), _position, !Game::ALLOW_TUNNEL, !Game::ALLOW_STAY)))
//	{
//
//		_direction = rand() % Game::NUM_OF_DIRECTION;
//	}
//}

void Ghost::move(const Point& pacmanPos)
{
	Point oldPos = _position;
	int xPos, yPos;
	xPos = _position.getX();
	yPos = _position.getY();
	switch (_direction) {
	case Game::DIRECTION::UP: 
		--yPos;
		_position.setY(yPos);
		break;
	case Game::DIRECTION::DOWN: // DOWN
		++yPos;
		_position.setY(yPos);
		break;
	case  Game::DIRECTION::LEFT: // LEFT
		--xPos;
		_position.setX(xPos);
		break;
	case Game::DIRECTION::RIGHT: // RIGHT
		++xPos;
		_position.setX(xPos);
		break;
	default:break;
	}

		Draw(oldPos,pacmanPos);

}



void Ghost::Draw(const Point& oldCoord,const Point& pacmanPos)
{
	if (Game::getGameMode() != Game::GAME_MODE::LOAD_SILENTLY)
	{
		int oldX = oldCoord.getX(), oldY = oldCoord.getY(), newX = _position.getX(), newY = _position.getY();
		char oldPosChar = GameBoard::getCurrBoardChar(oldX, oldY);
		gotoxy(oldX, oldY);
		if (Game::active_color)
			setTextColor(Color::LIGHTGREY);

		if (oldPosChar == GameBoard::EMPTY)
			_putch(GameBoard::BLANK);
		else
			_putch(oldPosChar);

		if (pacmanPos != _position)//not overwrite pacman figure
		{
			gotoxy(newX, newY);

			if (Game::active_color)
				setTextColor(Color::LIGHTGREEN);
			_putch(Ghost::FIGURE);
		}

	}
	


}

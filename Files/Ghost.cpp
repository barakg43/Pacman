#include "Ghost.h"
#include "Game.h"
#include "Point.h"
#include "GameBoard.h"
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
void Ghost::setIsMovement(bool value)
{
	_isMovement = value;
}
// Methods
void Ghost::pickDirection() // Chooses the next step of each ghost randomly, depends of the walls next to it
{

	while (!(Game::isValidDirection(getDirection(), _position, !Game::ALLOW_TUNNEL, !Game::ALLOW_STAY)))
	{

		_direction = rand() % Game::NUM_OF_DIRECTION;
	}
}
void Ghost::move()
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
	default:;
	}
	Ghost::Draw(oldPos);

}



void Ghost::Draw(const Point& oldCoord)
{
	int oldX = oldCoord.getX(), oldY = oldCoord.getY(), newX = _position.getX(), newY = _position.getY();
	char oldPosChar = GameBoard::getCurrBoardChar(oldX, oldY);
	gotoxy(oldX, oldY);
	if (Game::active_color)
		setTextColor(Color::LIGHTGREY);

	if(oldPosChar==GameBoard::EMPTY)
		_putch(GameBoard::BLANK); 
	else
		_putch(oldPosChar);

	if (Game::active_color)
		setTextColor(Color::LIGHTGREEN);
	gotoxy(newX, newY);


	_putch(Ghost::FIGURE);


}
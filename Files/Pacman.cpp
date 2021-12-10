
#include "GameBoard.h"
#include "Point.h"
#include "Game.h"
#include "Pacman.h"

//const Point Pacman::PACMAN_START_POS = { 46, 1 };

// Getters
const Point& Pacman::getPosition()
{
	return _position;
}
const int& Pacman::getLives() const
{
	return _lives;
}
const int& Pacman::getScore() const
{
	return _score;
}
// Setters
void Pacman::setPosition(const Point& pos)
{
	_position = pos;
}

void Pacman::Draw(const Point& old,bool withColor)
{
	
	gotoxy(old.getX(), old.getY());
	
	_putch(GameBoard::BLANK);
	gotoxy(_position.getX(), _position.getY());
	if (withColor)
		setTextColor(Color::YELLOW);
	_putch(FIGURE);
	
	

}
void Pacman::movePacman(int dir)
{
	int xPos, yPos;
	Point oldPos = _position;
	xPos = _position.getX();
	yPos = _position.getY();

	switch (dir) {
	case Game::DIRECTION::UP: 
		--yPos;
		if (yPos <= 0)
			yPos = GameBoard::getBoardHeight() - 1;
		_position.setY(yPos);
		break;
	case Game::DIRECTION::DOWN: 
		++yPos;
		if (yPos >= GameBoard::getBoardHeight() - 1)
			yPos = 0;
		_position.setY(yPos);
		break;
	case Game::DIRECTION::LEFT: 
		--xPos;
		if (xPos <= 0)
			xPos = GameBoard::getBoardWidth() - 1;
		_position.setX(xPos);
		break;
	case Game::DIRECTION::RIGHT: 
		++xPos;
		if (xPos >= GameBoard::getBoardWidth() - 1)
			xPos = 0;
		_position.setX(xPos);
		break;
	}
	Pacman::Draw(oldPos,0);
}
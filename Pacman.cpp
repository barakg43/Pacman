
#include "GameBoard.h"
#include "Point.h"
#include "Game.h"
#include "Pacman.h"




void Pacman::Draw(const Point& old)
{
	if (Game::getGameMode() != Game::GAME_MODE::LOAD_SILENTLY)
	{
		if (old != _position)
		{
			gotoxy(old.getX(), old.getY());
			_putch(GameBoard::BLANK);
		}
		gotoxy(_position.getX(), _position.getY());
		if (Game::active_color)
			setTextColor(Color::YELLOW);
		_putch(FIGURE);
		gotoxy(0, 0);
	}

	

}
void Pacman::movePacman()
{
	int xPos, yPos;
	Point oldPos = _position;
	xPos = _position.getX();
	yPos = _position.getY();

	switch (_direction) {
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
	
		Draw(oldPos);
}

#include "Fruit.h"
#include "GameBoard.h"
#include "Game.h"

 void Fruit::draw(Point& oldCoord)
{

	 int oldX = oldCoord.getX(), oldY = oldCoord.getY(), newX = _position.getX(), newY = _position.getY();
	 char oldPosChar = GameBoard::getCurrBoardChar(oldX, oldY);
	 gotoxy(oldX, oldY);
	 if (Game::active_color)
		 setTextColor(Color::LIGHTGREY);
	 _putch(oldPosChar);

	 if (Fruit::isOnScreen())
	 {
		 gotoxy(newX, newY);
		 if (Game::active_color)
			 setTextColor(Color::LIGHTRED);
		 _putch(Fruit::getFigure());
	 }
	 
	 

}



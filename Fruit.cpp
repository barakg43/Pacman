
#include "Fruit.h"
#include "GameBoard.h"
#include "Game.h"

 void Fruit::Draw(const Point& oldCoord, const Point& pacmanPos)
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

		 if (isOnScreen() && pacmanPos != _position)
		 {
			 gotoxy(newX, newY);
			 if (Game::active_color)
				 setTextColor(Color::LIGHTRED);
			 _putch(FIGURE);
		 }
	 }


}
 void Fruit::newFigure(string& stepStr, const string& stepFile, int line) {

	
	 if (Game::getGameMode() == Game::GAME_MODE::SAVE || Game::getGameMode() == Game::GAME_MODE::SIMPLE)
	 {
		 FIGURE = '0' + 5 + rand() % 5;/*random number between 5 - 9;*/

		 if (Game::getGameMode() == Game::GAME_MODE::SAVE)
			 stepStr[Game::getFruitFigureIndexStepsString()] = FIGURE;
	 }
	 else//game mode is load or load -silent
	 {
		 FIGURE = stepStr[Game::getFruitFigureIndexStepsString()];

		 if (FIGURE < '5' || FIGURE>'9')
			 throw Game::excepMgr.insertExcp("invaild fruit Figure '" + string{ FIGURE } + "' in step file '" + stepFile + "' \nin line: " + std::to_string(line)
				 + "\n Figure can be only the characters '5' to '9' ");

	 }
 }
 void Fruit::disappearFruit()
 {
	 _onScreen = false;
	 Draw(_position, {0,0});
	 _oldFruitPos = _position;
	 _position.setX(NOT_INIT);
	 _position.setY(NOT_INIT);

 }
 void Fruit::resetFruit()
 {
	 _oldFruitPos = _position;
	
	
	 _position.setX(NOT_INIT);
	 _position.setY(NOT_INIT);
	setFruitOnScreen(false);
	 setIsMovement(false);


 }

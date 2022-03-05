#pragma once
#include"GameBoard.h"
#include "Point.h"
#include "Ghost.h"
#include <ctime>
#include <string.h>
using std::string;

class Fruit:public Ghost
{

	
private:
	int _onScreen;//check if the fruit is on screen or not
	int _fruitTimeSpan;//total time a fruit can stay  on  screen before it disappears
	const char NOT_INIT = 85;
	//char _figure;
	Point _oldFruitPos;
public:
	
	const int FRUIT_TIME_SPAN = 45;
	Fruit()
	{
		FIGURE = '0';//fruit figure not initilized
		_fruitTimeSpan = FRUIT_TIME_SPAN;
		_onScreen = false;
		_isMovement = false;
		_position.setX(NOT_INIT);//put fruit outside screen
		_position.setY(NOT_INIT);
		
	}
	const Point& getOldPos() { return _oldFruitPos; }
	void newFigure(string& stepStr, const string& stepFile, int line);
	void setFigure(char figure) { FIGURE = figure; }
	char getFigure() const{ return FIGURE; }
	int isOnScreen() { return _onScreen; }
	void setFruitOnScreen(const int choice) { _onScreen = choice; }
	void  setTimeSpan(const int num){	_fruitTimeSpan = num;}
	int checkTimeSpan() { return _fruitTimeSpan; }
	void disappearFruit();
	void resetFruit();

	 void Draw(const Point& oldCoord, const Point& pacmanPos)override;

};
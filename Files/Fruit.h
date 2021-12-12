#pragma once

#include "Point.h"
#include "Ghost.h"
#include <ctime>
#define FRUIT_INIT_POSITION {46,1}
#define FRUIT_TIME_SPAN 45

class Fruit:public Ghost
{

	
private:
	int _onScreen;//check if the fruit is on screen or not
	int _fruitTimeSpan;//total time a fruit can stay  on  screen before it disappears
	
	
	char _figure;
	
public:
	Fruit()
	{
		_figure = '0';//fruit figure not initilized
		_fruitTimeSpan = FRUIT_TIME_SPAN;
		_onScreen = false;
		_isMovement = false;
	
	}
	void setFigure(char num) { _figure = num; }
	char getFigure() { return _figure; }
	int isOnScreen() { return _onScreen; }
	void setFruitOnScreen(int choice) { _onScreen = choice; }
	void  setTimeSpan(int num){	_fruitTimeSpan = num;}
	int checkTimeSpan() { return _fruitTimeSpan; }
	void draw(Point& oldPos);

};
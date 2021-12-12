#pragma once
#include <iostream>
#include "Point.h"
#include "GameBoard.h"
class GameObject
{
protected:
	char _figure;
	Point _position;

public:

	inline Point getPosition() const
	{
		return _position;
	}
	inline void setPosition(const Point& pos) {
		_position = pos;
	}
	inline void setFigure(char figure)
	{
		_figure = figure;
	}
	inline char getFigure()const
	{
		return _figure;
	}
	void draw(Point& oldPos, char oldBoardChar,bool withColor)
	{

		

		int oldX = oldPos.getX(), oldY = oldPos.getY(), newX = this->getPosition().getX(), newY = this->getPosition().getY();

		if (withColor)
			setTextColor(LIGHTGREY);
		gotoxy(oldX, oldY);
		_putch(oldBoardChar);


		if (withColor)
		{
			if (this->getFigure() == '@')
				setTextColor(YELLOW);
			else if (this->getFigure() == '$')
				setTextColor(LIGHTGREEN);
			else
				setTextColor(LIGHTGREY);
			
		}
		gotoxy(_position.getX(), _position.getY());
		_putch(_figure);

	}

};
#pragma once
#include "Point.h"


class Ghost
{
private:

	Point _position; // array of two ghosts in game
	bool _isMovement;
	int _direction; // field that mentions if the ghosts can move. true - yes, false - no
public:
	const char FIGURE = '$';
	// Constructors
	Ghost(Point ghost = { 3, 1 }, bool movement = true) : _position(ghost), _isMovement(movement), _direction(1) {}
	// Getters
	Point& getPosition();

	bool getMovement() const;
	// Setters
	void setPosition(const Point& pos);
	void setIsMovement(bool value);
	// Methods
	void pickDirection();
	int getDirection()const;
	void move();
	
	void Draw(const Point& oldCoord);
};
#pragma once
#include "Point.h"
#include "Move.h"
class Ghost
{
protected:

	Point _position; // array of two ghosts in game
	bool _isMovement;// field that mentions if the ghosts can move. true - yes, false - no
	int _direction; 
	Move* moveStrategy=nullptr;//allocate by heap
	char FIGURE = '$';
	
public:
	
	// Constructors
	Ghost(Point ghost = { 3, 1 }, bool movement = false) : _position(ghost), _isMovement(movement), _direction(1) {}
	// Getters
	Point& getPosition();

	virtual ~Ghost() { delete moveStrategy; }
	Ghost(const Ghost& other) = delete;
	Ghost& operator=(const Ghost& other) = delete;
	bool getMovement() const;
	// Setters
	void setPosition(const Point& pos);
	void setIsMovement(bool value);
	// Methods
	void setDirection(int dir);
//	void pickDirection();
	int getDirection()const;
	void move(const Point& pacmanPos);
	void setMoveStrategy(char ghostLevel);
	Move*& getMoveStrategy();
	
	virtual void Draw(const Point& oldCoord, const Point& pacmanPos);
};

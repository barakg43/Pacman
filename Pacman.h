#pragma once
#include "Point.h"
//#include "Game.h"

class Pacman
{
private:
	const char FIGURE = '@';
	Point PACMAN_START_POS = { 0,0 };
	Point _position; // Coordination is automatically (40, 13)
	char _direction=-1;
	int _lives;
	int _score;
public:
	// Constructors
	Pacman() :_position(PACMAN_START_POS)
	{
		// Point was already created and defined
		resetPacmanData(); }
	Pacman(const Point& pos, int lives = 3, int score = 0) :_position(pos), _lives(lives), _score(score) {}
	// Getters
	const Point& getPosition() {     return _position;  }
	 int getLives() const {    return _lives;     }
	 int getScore() const {	 return _score;     }
	 int getDirection()const { return _direction; }
	// Setters
	void setDirection(int dir) { _direction = dir; }
	void setPosition(const Point& pos) { _position = pos; }
	int getAndUpdateLife() { return --_lives; }
	int getAndUpdateScore() { return _score++; }
	void addFruitToScore(char fruitNum) { _score += (fruitNum - '0'); }
	// Methods
	void resetPacmanData() {
		_lives = 3;
		_score = 0; }
	void movePacman();
	void Draw(const Point& old);
};
#pragma once
#include "Point.h"


class Pacman
{
private:
	const char FIGURE = '@';
	Point PACMAN_START_POS = { 0,0 };
	Point _position; // Coordination is automatically (40, 13)
	int _lives;
	int _score;
public:
	// Constructors
	Pacman() :_position(PACMAN_START_POS)
	{
		// Point was already created and defined
		resetPacmanData();

	};
	Pacman(const Point& pos, int lives = 3, int score = 0) :_position(pos), _lives(lives), _score(score) {}
	// Getters
	const Point& getPosition();
	const int& getLives() const;
	const int& getScore() const;
	// Setters
	void setPosition(const Point& pos);
	int getAndUpdateLife() { return --_lives; }
	int getAndUpdateScore() { return _score++; }
	// Methods
	void resetPacmanData() {
		_lives = 3;
		_score = 0;
	};
	void movePacman(int dir);
	void Draw(const Point& old,bool withColor);
};
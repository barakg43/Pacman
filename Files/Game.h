#pragma once
//#include "Headers.h"
#include "Ghost.h"
#include "Point.h"
#include "Pacman.h"
#include "GameMenu.h"
class GameBoard;

class Game
{
public:
	enum DIRECTION { UP, DOWN, LEFT, RIGHT, STAY ,SIZE, NUM_OF_DIRECTION = 4};
	enum { ALLOW_STAY = 1, ALLOW_TUNNEL = 1, NORMAL_GAME_SPEED = 150, SLOW_GAME_SPEED = 250, FAST_GAME_SPEED = 75 };
	static bool active_color;
	enum GHOSTS { MAX_GHOSTS = 4, MOVE_COUNTER_ROUNDS = 10 };//	friend class Pacman;
private:
	static GameBoard _board; // print class
	enum OPTION { ESC = 27, NOT_INIT = -1 };
	Point GHOSTS_START_POS[MAX_GHOSTS];
	Point PACMAN_START_POS;
	Pacman _pacman{ PACMAN_START_POS };
	Ghost _ghosts[MAX_GHOSTS];
	char pacmanDir = NOT_INIT, tempDir = NOT_INIT;;
	static int gameSpeed;
	
	char _arrowKeys[DIRECTION::SIZE][2]; // the only allowed keys are: { 'w', 'W', 'a', 'A', 'x', 'X', 'd', 'D', 's', 'S' }
	enum KEYS{ w = 'w', W = 'W', a = 'a', A = 'A', x = 'x', X = 'X', d = 'd', D = 'D', s = 's', S = 'S' };
	int _moveCounter;
	int ghostsSize = 0;
	int gameOption=NOT_INIT;
	GameMenu gameMenu;
	void resetGame();
public:

	//Constructors
	Game();


	void start();
	static bool isValidDirection(int key, const Point& currPos, bool allowedTunnel, bool allowStay);
	static void setGameSpeed(int speed);
	void gameLoop();
	

private://Met

	
	void getCreaturesInitPos();
	void checkPacmanHitsGhosts();
	void moveGhosts();
	void resetAllCharactersToInitPos();
	void pauseMode(bool& gamePause);
	int convertKeyToDirection(char key);


};
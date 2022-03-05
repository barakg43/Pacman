#pragma once
#include "Fruit.h"
#include "Ghost.h"
#include "Point.h"
#include "Pacman.h"

#include "GameMenu.h"
#include "ExceptionsManager.h"
#include <iostream>
#include <fstream>
#include <map>
using std::cout; 
using std::endl;
using std::fstream;
class GameBoard;

class Game
{
public:
	enum DIRECTION { UP, DOWN, LEFT, RIGHT, STAY, SIZE, NUM_OF_DIRECTION = 4 };
	enum { ALLOW_STAY = 1, ALLOW_TUNNEL = 1, FAST_GAME_SPEED = 60, NORMAL_GAME_SPEED = 120, SLOW_GAME_SPEED = 200 };
	static bool active_color;
	enum GHOSTS { MAX_GHOSTS = 4, MOVE_COUNTER_ROUNDS = 10, GOOD_GHOST_RANDOM_ROUNDS = 5 };
	enum GAME_MODE{SIMPLE=100,SAVE,LOAD,LOAD_SILENTLY};
	enum OPTION { ESC = 27, NOT_INIT = 9 };
	static ExceptionsManager excepMgr;
	static short  getGameMode() { return _gameMode; }
private:
	std::map<int, char> directionMap{
		{DIRECTION::UP,'U'},
		{DIRECTION::DOWN,'D'},
		{DIRECTION::LEFT,'L'},
		{DIRECTION::RIGHT,'R'},
		{DIRECTION::STAY,'S'},
		{OPTION::NOT_INIT,'N'}
	};


	static GameBoard _board; // print class
	enum FRUIT { FRUIT_RANDOM_APRR = 100, FRUIT_MAX_MOVES = 7 };
	Point GHOSTS_START_POS[MAX_GHOSTS];
	Point PACMAN_START_POS;
	Pacman _pacman{ PACMAN_START_POS };
	Ghost _ghosts[MAX_GHOSTS];
	Fruit _fruit;
	GameMenu gameMenu;
	static short _gameMode;
	char tempDir = NOT_INIT;
	static int gameSpeed;
	static int ghostsLevel;


	char _arrowKeys[DIRECTION::SIZE][2]; // the only allowed keys are: { 'w', 'W', 'a', 'A', 'x', 'X', 'd', 'D', 's', 'S' }
	enum KEYS { w = 'w', W = 'W', a = 'a', A = 'A', x = 'x', X = 'X', d = 'd', D = 'D', s = 's', S = 'S' };
	int _moveGhostCounter;
	static int ghostsSize;
	int _goodGhostRandomMovesCounter[MAX_GHOSTS] = { 0 };
	int  _fruitMoveCounter = 0;
	int _randomLoop = NOT_INIT;
	int gameOption=NOT_INIT;
	bool toRunGame=false;
	int stepCounter;
	string screenFileNameOnly;
	fstream stepsFile;
	string stepsFileName;
	const string STEPS_FILE_EXT = ".steps";
	const string RESULT_FILE_EXT = ".result";
	const string STEPS_FORMAT = "Pac:d Fru:app=f fig=F x=XX y=YY dir=d G1:d G2:d G3:d G4:d ;\n";
	string stepsString = STEPS_FORMAT;
	enum STEPS_INDEX{ PACMAN =4,FRUIT_APP=14,FRUIT_FIGURE=20,FRUIT_X=24, FRUIT_Y=29,FRUIT_DIR=36,GHOSTS=41};
	fstream resultFile;
	string resultFileName;
	bool invalidArguments = false;
	bool atLeast1BoardFinish = false;
	enum  CMD_ARGUMENT{SAVE_ARG,LOAD_ARG,SILENT_ARG};
	std::map<int,const char*> commandArgumentMap{
		{ CMD_ARGUMENT::SAVE_ARG,"-save"},
		{ CMD_ARGUMENT::LOAD_ARG,"-load"},
		{ CMD_ARGUMENT::SILENT_ARG,"-silent"}
	};
public:

	//Constructors
	Game();

	void start();
	/*add this function before the function 'start' to run game with command arguments*/
	void getCommandLineArguments(int argc, char** argv);
	static bool isValidDirection(int key, const Point& currPos, bool allowedTunnel, bool allowStay);
	static void setGameSpeed(int speed);
	static void setGhostsLevel(char option);
	void gameLoop();
	static int getGhostNumber() {return ghostsSize;}
	static int getFruitFigureIndexStepsString(){ return STEPS_INDEX::FRUIT_FIGURE; }
private:// Methods
	
	
	void saveAndCheckResultFile(const string& msg, bool boardEnded);
	void getNewValidRandomPositionFruit();
	void getCreaturesInitPos();
	void checkPacmanHitsGhosts();
	void moveGhosts();
	void resetAllCreaturesToInitPos();
	void openStepsAndResultFiles(const string& screenFileName);
	int convertKeyToDirection(char key);
	void UpdateFruitMoves();
	void checkPacmanEatFruit();
	void checkFruitHitGhost();
	void checkForUserInput(bool& isGamePause);
	void invalidDirectionInStepFileException(char dir, const string& creatureName);
	void getCurrStepAndMsgFromResultFile(int& currStep, string& msg);
	void randomFruit();
	void saveStepsToFile();
	int convertDirFromFile(char dir, const string& creatureName);
	void getNextGameSteps();
	void debugGhost(int offset, string fun);
};

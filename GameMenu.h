#pragma once
#include<iostream>
#include <string>
using std::string;
using std::clog;
using std::cout;

class GameMenu
{

	int gameOption;
	enum SPEED { FAST = '1', NORMAL, SLOW };
	enum GHOSTS_LEVEL { BEST = 'a', GOOD = 'b', NOVICE = 'c' };
	string boardfileName;
public:
	enum OPTION { NOT_INIT = -1, START = '1', WITH_COLORS, CHANGE_GAME_SPEED,GHOSTS_MENU,LOAD_SPECIFIC_SCREEN, HOW_TO_PLAY = '8', EXIT = '9' };
	enum GHOST_TYPE{ BEST_GHOST_LEVEL = 'a', GOOD_GHOST_LEVEL = 'b', NOVICE_GHOST_LEVEL = 'c' };
	GameMenu():gameOption(NOT_INIT){}

	void Print(bool& run);
	int getCurrGameOption() { return gameOption;}
	void setGameOption(int opt) { gameOption = opt; }
	void gameEnd(int lives_pac,bool atLeast1BoardFinish);
	const string& getBoardFileName() { return boardfileName; }
private:

	
	void printPacmanLogo();
	void checkIfBoardFileExist(bool& runGame);
    int  getGameMenuOptionFromUser();
    void howToPlay();
	void gameSpeedMenu();
	void ghostsLevelMenu();
	string GetFileExtension(const string& FileName);



};

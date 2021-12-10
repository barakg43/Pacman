#pragma once
#include<iostream>
#include <string>
using std::clog;
using std::cout;

class GameMenu
{
//	enum OPTION;
	int gameOption;
	enum SPEED { FAST = 1, NORMAL, SLOW };
	
public:
	enum OPTION { NOT_INIT = -1, START = 1, WITH_COLORS, CHANGE_GAME_SPEED, HOW_TO_PLAY = 8, EXIT = 9 };
	GameMenu():gameOption(NOT_INIT){}
//	void print();
	void Print(bool& run);
	int getCurrGameOption() { return gameOption;}
	void setGameOption(int opt) { gameOption = opt; }
	void gameEnd(int lives_pac);
private:
	//void gameMenu();
	
  
    int  getGameMenuOptionFromUser();
    void howToPlay();
	void gameSpeedMenu();




};
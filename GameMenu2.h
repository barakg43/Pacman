#pragma once

class GameMenu
{
	 int gameOption;

public:
	void print();
	enum SPEED{FAST=1,NORMAL,SLOW};
	enum OPTION{ NOT_INIT =-1};
	int getCurrGameOption{ return gameOption; }
private:
	void gameMenu();
	int getGameMenuOptionFromUser();
	void howToPlay();
	void gameSpeedMenu();




};


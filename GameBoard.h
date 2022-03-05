#pragma once


#include<iostream>
#include "io_utils.h"
#include <fstream>
#include "Point.h"
#include <list>
#include <iterator>
#include <string>
#include "Pacman.h"

using std::cout;
using std::cin;
using std::istream;
using std::ifstream;
using std::list;
using std::string;
class Game;
class GameBoard
{

public:

	enum { MAX_HEIGHT = 25, MAX_WIDTH = 80, WALL = '#', BREADCRUMBS = '.', BLANK = ' ', EMPTY = '%', PACMAN = '@', GHOST = '$', LEGEND = '&' };
	static const string SCREEN_FILE_EXT;
	
private:
	Point pacmanInitPos;
	enum { MAX_GHOSTS = 4 };
	Point ghostsInitPos[MAX_GHOSTS]; //not use Game::GHOSTS::MAX_GHOSTS to avoid cyclic dependency
	static Point legendPos;
	static int width, height;

	int sumBreadCrumbsInBoard = 0;//to count how many breadcrumbs 'fillBreadCrumbs()' create
	static char board[MAX_HEIGHT][MAX_WIDTH + 2];//+2   '/n' and '/0'
	int ghost_num = 0;
	list<string> screenFileNames;
	list<string>::iterator nextFileName;
	
public:
	string getNextScreenFileName();
	void getAllScreenFile();
	// Constructors
	GameBoard();
	void addScreenFileName(const string& fileName) { screenFileNames.push_back(fileName); }
	void getGhostsPos(Point*& pos, int& size);
	const Point& getPacmanPos();
	static bool checkIfLegendAera(const Point& pointTocheck);
	void print();
	static void printScoreToScreen(const int& score);
	static void printLivesToScreen(const int& lives);
	int getSumOfBreadCrumbsInBoard()const { return  sumBreadCrumbsInBoard; }

	void removeBreadCrumbsInPacmanPos(const Point& pos);
	static char getCurrBoardChar(int x, int y) { return board[y][x]; }
	void clearBreadcumbsInBoard(int x, int y);
	static void clearScreen() { system("cls"); }
	void clearFileNameList() { screenFileNames.clear(); }
	static int getBoardHeight(){ return height; }
	static int getBoardWidth() { return width; }
	void loadBoardFromFile(const string& fileName);
	void resetToFirstScreenFileName() { nextFileName = screenFileNames.begin(); }
	bool isScreenFileNameListEmpty();
	void printPauseMode(bool& gamePause,const Pacman& pac);
private:
	void checkForBoardExceptions(int sumPacman,int sumLengend, int width, const string& fileName);
	unsigned int copyLineToRow(const string& src, char* row, unsigned int size);
	void printLegendText();
	void clearLegendAera();
	void saveSpaceLegendFirstLine();
	void initBoard();
	void fillBreadCrumbs();
};

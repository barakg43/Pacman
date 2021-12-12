#pragma once

//#include "Headers.h"

#include<iostream>
#include "io_utils.h"
#include <fstream>
#include "Point.h"
#include <list>
#include <iterator>
using std::cout;
using std::cin;
using std::istream;
using std::list;

class GameBoard
{

public:

	enum { MAX_HEIGHT = 25, MAX_WIDTH = 80, WALL = '#', BREADCRUMBS = '.', BLANK = ' ', EMPTY = '%', PACMAN = '@', GHOST = '$', LEGEND = '&' };
	
	Point pacmanInitPos;
private:
	const string SCREEN_FILE_EXT = ".screen";
	enum { MAX_GHOSTS = 4 };
	Point ghostsInitPos[MAX_GHOSTS]; //not use Game::GHOSTS::MAX_GHOSTS to avoid cyclic dependency
	static Point legendPos;
	static int width, height;
	int sumBreadCrumbsInBoard = 0;//to count how many breadcrumbs 'fillBreadCrumbs()' create
	int sumBreadCrumbEated = 0;
	static char board[MAX_HEIGHT][MAX_WIDTH + 2];//+2   '/n' and '/0'
	int ghost_num = 0;
	list<string> screenFileNames;
	list<string>::iterator nextFileName;
	
public:
	string getNextScreenFileName();
	void getAllScreenFile();
	// Constructors
	GameBoard();
	void getGhostsPos(Point*& pos, int& size);
	const Point& getPacmanPos();
	
	void print();
	static void printScoreToScreen(const int& score);
	static void printLivesToScreen(const int& lives);
	int getSumOfBreadCrumbsInBoard()const { return  sumBreadCrumbsInBoard; }
	int getSumBreadCrumbEated()const{ return  sumBreadCrumbEated; }
//	void updateSumBreadCrumbEated() { sumBreadCrumbEated++; }
	void removeBreadCrumbsInPacmanPos(const Point& pos);
	static char getCurrBoardChar(int x, int y) { return board[y][x]; }
	void clearBreadcumbsInBoard(int x, int y);
	static void clearScreen() { system("cls"); }
//	void resetBoard();
	static int getBoardHeight(){ return height; }
	static int getBoardWidth() { return width; }
	void loadBoardFromFile(string fileName);
	void resetToFirstScreenFileName() { nextFileName = screenFileNames.begin(); }
	bool isScreenFileNameListEmpty();
private:
	unsigned int copyLineToRow(const string& src, char* row, unsigned int size);
	void clearLegendAera();
	void saveSpaceLegendFirstLine();
	void initBoard();
	void fillBreadCrumbs();
};
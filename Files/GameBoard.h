#pragma once

//#include "Headers.h"

#include<iostream>
#include "io_utils.h"
#include <fstream>
#include "Point.h"

#include <vector>
using std::cout;
using std::cin;
using std::istream;


class GameBoard
{

public:

	enum { MAX_HEIGHT = 25, MAX_WIDTH = 80, WALL = '#', BREADCRUMBS = '.', BLANK = ' ', EMPTY = '%', PACMAN = '@', GHOST = '$', LEGEND = '&' };
	
	Point pacmanInitPos;
private:
	vector<string> screenFileNames;
	enum { MAX_GHOSTS = 4 };
	Point ghostsInitPos[MAX_GHOSTS]; //not use Game::GHOSTS::MAX_GHOSTS to avoid cyclic dependency
	static Point legendPos;
	static int width, height;
	int numOfBreadCrumbs = 0;//to count how many breadcrumbs 'fillBreadCrumbs()' create
	static char board[MAX_HEIGHT][MAX_WIDTH + 2];//+2   '/n' and '/0'
	int ghost_num = 0;
	
public:
	void getAllScreenFile();
	// Constructors
	GameBoard();
	void getGhostsPos(Point*& pos, int& size);
	const Point& getPacmanPos();
	
	void print();
	static void printScoreToScreen(const int& score);
	static void printLivesToScreen(const int& lives);
	int getNumberOfBreadCrumbs() { return numOfBreadCrumbs; }
	void removeBreadCrumbsInPacmanPos(const Point& pos);
	static char getCurrBoardChar(int x, int y) { return board[y][x]; }
	void clearBreadcumbsInBoard(int x, int y);
	static void clearScreen() { system("cls"); }
	void resetBoard();
	static int getBoardHeight(){ return height; }
	static int getBoardWidth() { return width; }
	void loadBoardFromFile(string fileName);
private:
	int copyLineToRow(const string& src, char* row, int size);
	void clearLegendAera();
	void saveSpaceLegendFirstLine();
	void initBoard();
	void fillBreadCrumbs(bool isGameReset);
};
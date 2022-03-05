
#include "GameBoard.h"
#include "Game.h"
#include "Point.h"
#include <string.h>
#include <list>
#include <filesystem>
using std::list;
using std::filesystem::directory_iterator;
using std::filesystem::path;


const string GameBoard::SCREEN_FILE_EXT = ".screen";
int GameBoard::width = 0;
int GameBoard::height=0;
Point GameBoard::legendPos;
char GameBoard::board[MAX_HEIGHT][MAX_WIDTH + 2] = { {BLANK} };

GameBoard::GameBoard() {}
void GameBoard::initBoard()
{
	for (int row = 0; row < MAX_HEIGHT; row++)
	{
		for (int col = 0; col < MAX_WIDTH; col++)
		{
			board[row][col] = BLANK;

		}
		board[row][MAX_WIDTH] = '\0';
	}
	

}
const Point& GameBoard::getPacmanPos()
{
	return pacmanInitPos;
}

string GameBoard::getNextScreenFileName()
{
	string res = *nextFileName;
	nextFileName++;
	return res;
}
bool GameBoard::isScreenFileNameListEmpty()
{
	return (nextFileName == screenFileNames.end());
}
void GameBoard::getGhostsPos(Point*& pos, int& size)
{
	pos = ghostsInitPos;
	size = ghost_num;
}

void GameBoard::getAllScreenFile()
{

	for (const auto& entry : directory_iterator(std::filesystem::current_path()))
	{
		string fileExtension = entry.path().filename().extension().string();
		if (fileExtension == SCREEN_FILE_EXT)
			screenFileNames.push_back(entry.path().filename().string());
			
	}
}
void GameBoard::print()
{

	if (Game::getGameMode() != Game::GAME_MODE::LOAD_SILENTLY)
	{
		clearScreen();

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width + 1 && board[i][j] != '\0'; j++)
			{
				switch (board[i][j])
				{
				case WALL:
					if (Game::active_color)
						{setTextColor(Color::LIGHTCYAN);}
					_putch(board[i][j]);
					break;
				case BREADCRUMBS:
					if (Game::active_color)
						{setTextColor(Color::LIGHTGREY);}
					_putch(board[i][j]);
					break;
				case EMPTY:;//print ' ' insted
				default:
					_putch(BLANK);
					break;
				}
			}
			cout << endl;
		}
		
		printLegendText();
	}
	
}

void GameBoard::printLegendText()
{
	if (Game::active_color)
		setTextColor(Color::LIGHTGREY);
	gotoxy(legendPos.getX(), legendPos.getY());
	cout << "Lives:              ";
	gotoxy(legendPos.getX(), legendPos.getY() + 1);
	cout << "Score:              ";
	gotoxy(legendPos.getX(), legendPos.getY() + 2);
	cout << "                    ";
	
}


void GameBoard::clearLegendAera()
{
	int x = legendPos.getX();
	int y = legendPos.getY();

	for (int row = y; row < y +3&&row<MAX_HEIGHT; row++)
		for (int col = x; col < x+20 &&col<MAX_WIDTH; col++)
			{ board[row][col] = EMPTY; }


}

void GameBoard::loadBoardFromFile(const string& fileName)
{
	int countPacMan = 0;
	int countLegend = 0;
	ghost_num = 0;
	width = height = 0;
	bool firstPacmanPos = true;
	bool firstLegendPos = true;
	sumBreadCrumbsInBoard = 0;
	initBoard();
	ifstream boardFile(fileName);
	
		if (boardFile)
		{
			string temp;
			int row;
			getline(boardFile, temp);
			width = copyLineToRow(temp, board[0], MAX_WIDTH);
			saveSpaceLegendFirstLine();
			board[0][width] = '\n';
			board[0][width+1] = '\0';
			for (row = 1; row < MAX_HEIGHT&& !boardFile.eof(); row++)
			{	
				getline(boardFile, temp);
				copyLineToRow(temp, board[row], width);
					board[row][width] = '\n';
					board[row][width + 1] = '\0';
			}
			height = row ;

			for (int row = 0; row < height; row++)
				for (int col = 0; col < width; col++)
				{

					switch (board[row][col])
					{
					case PACMAN:
							pacmanInitPos = { col,row };
							firstPacmanPos = false;
							countPacMan++;
							board[row][col] = BLANK;
						break;
					case GHOST:
						if (ghost_num < Game::GHOSTS::MAX_GHOSTS)
						{
							ghostsInitPos[ghost_num] = { col,row };
							ghost_num++;//index of ghostsInitPos[]
						}
						board[row][col] = BLANK;
						break;
					case LEGEND:
							legendPos = { col,row };
							countLegend++;
							board[row][col] = BLANK;
						break;
					case WALL:;
					case EMPTY:break;
					default:
						board[row][col] = BLANK;

					}

				}
			
			int yLegend = legendPos.getY();
			/*the legend position in the last 2 board row,increase height of board game*/
			if (yLegend + 2 >= height&& yLegend + 2 < MAX_HEIGHT)
			{
			
				height = yLegend + 2;
				board[yLegend + 1][width] = '\n';
				board[yLegend + 1][width + 1] = '\0';
				board[yLegend + 2][width] = '\n';
				board[yLegend + 2][width + 1] = '\0';
			}
			

			clearLegendAera();
			fillBreadCrumbs();
			checkForBoardExceptions(countPacMan,countLegend,width, fileName);
		}
		else
		{
			throw Game::excepMgr.insertExcp("faild to open the file " + fileName);
			
		}


}
unsigned int GameBoard::copyLineToRow(const string& src, char* row, unsigned int size)
{
	unsigned int len;
	for (len = 0; len < size && len < (unsigned int)src.length(); len++)
		row[len] = src[len];

	return len;

}
void GameBoard::printPauseMode(bool& gamePause, const Pacman& pac)
{
	
		if (!gamePause)
		{
			gotoxy(legendPos.getX(), legendPos.getY());
			cout << "Game Pause!  press  ";
			gotoxy(legendPos.getX(), legendPos.getY() + 1);
			cout << "ESC to continue or g";
			gotoxy(legendPos.getX(), legendPos.getY() + 2);
			cout << "return game menu....";
		}
		else
		{
			printLegendText();    
			printLivesToScreen(pac.getLives());
			printScoreToScreen(pac.getScore());
			
		}

		gamePause ^= true;//switch between modes

}
void GameBoard::saveSpaceLegendFirstLine() {

	for (int i = 0; i < width; i++)
		if (board[0][i] == LEGEND)
		{
			board[0][width] = BLANK;
			if (i + 20 <= MAX_WIDTH)
				width = i + 20;
			return;
		}
}

void GameBoard::printScoreToScreen(const int& score)
{
	if (Game::getGameMode() != Game::GAME_MODE::LOAD_SILENTLY)
	{
		if (Game::active_color)
			setTextColor(Color::LIGHTGREY);
		gotoxy(legendPos.getX() + 7, legendPos.getY() + 1);
		cout << score;
	}
}
void GameBoard::printLivesToScreen(const int& lives)
{
	if (Game::getGameMode() != Game::GAME_MODE::LOAD_SILENTLY)
	{
		if (Game::active_color)
			setTextColor(Color::LIGHTGREY);

		gotoxy(legendPos.getX() + 7, legendPos.getY());
		cout << lives;
	}
}
//the erase the invisible breadcrumbs in Pacman init position
void GameBoard::removeBreadCrumbsInPacmanPos(const Point& pos)
{
	clearBreadcumbsInBoard(pos.getX(), pos.getY());
}
void GameBoard::clearBreadcumbsInBoard(int x, int y)
{
	sumBreadCrumbsInBoard--;

	board[y][x] = BLANK;
}
bool GameBoard::checkIfLegendAera(const Point& pointTocheck)
{
	int x = legendPos.getX();
	int y = legendPos.getY();
	int xPoint = pointTocheck.getX();
	int yPoint=  pointTocheck.getY();


	for (int row = y; row < y + 3 && row < MAX_HEIGHT; row++)
		for (int col = x; col < x + 20 && col < MAX_WIDTH; col++)
		{
			if (row == yPoint && col == xPoint)
				return true;
		}

	return false;
}


void GameBoard::fillBreadCrumbs()
{
	for (int row = 1; row < height-1; row++)
	{
		for (int col = 1; col < width-1; col++)
			if (board[row][col] == BLANK)
			{
				board[row][col] = BREADCRUMBS;
				sumBreadCrumbsInBoard++;
			}
	}
}


void GameBoard::checkForBoardExceptions(int sumPacman, int sumLengend,int width, const string& fileName)
{
	bool throwExc = false;
	if(width==0)
	{
		Game::excepMgr.insertExcp("invaild board width in file '"+ fileName+"' : "+ std::to_string(width));
		throwExc = true;
	}
	if (sumPacman == 0)
	{
		Game::excepMgr.insertExcp("missing pacman in the board file:"+ fileName);
		throwExc = true;
	}

	else if (sumPacman > 1)
	{
		Game::excepMgr.insertExcp(" more then 1 pacman in the board file:" + fileName);
		throwExc = true;
	}
	if (sumLengend == 0)
	{
		Game::excepMgr.insertExcp("missing lengend in the board file:" + fileName);
		throwExc = true;
	}
	
	else if (sumLengend > 1)
	{
		Game::excepMgr.insertExcp(" more then 1 lengend in the board file:" + fileName);
		throwExc = true;
	}
	else//only one legend
	{
		if (legendPos.getY() + 3 > MAX_HEIGHT)
		{
			Game::excepMgr.insertExcp(" the legend in " + fileName+ " is overflow the max board height "  + std::to_string(GameBoard::MAX_HEIGHT)
				+ ",the board missing " + std::to_string(legendPos.getY() + 3 - MAX_HEIGHT) + " lines for legend");
			throwExc = true;
		}
		if (legendPos.getX() + 20 > MAX_WIDTH)
		{
			Game::excepMgr.insertExcp("the legend in " + fileName + " is overflow the max board width " + std::to_string(GameBoard::MAX_WIDTH)
				+ ",the board missing " + std::to_string(legendPos.getX() + 20 - MAX_WIDTH) + " cols for legend");
			throwExc = true;
		}
		else if (legendPos.getX() + 20 > width)
		{
			Game::excepMgr.insertExcp("the legend in " + fileName + " is overflow the board width " + std::to_string(width)
				+ ",the board missing" + std::to_string(legendPos.getX() + 20 - width) + " cols for legend");
			throwExc = true;
		}
	}

	if (throwExc)
		throw &Game::excepMgr;
	

}
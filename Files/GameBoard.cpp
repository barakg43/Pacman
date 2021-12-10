
#include "GameBoard.h"
//#include "Headers.h"
#include "Game.h"
#include "Point.h"
#include <string.h>
#include <filesystem>

using std::filesystem::directory_iterator;
using std::filesystem::path;

// Constructors

int GameBoard::width = 0;
int GameBoard::height=0;
Point GameBoard::legendPos;
char GameBoard::board[MAX_HEIGHT][MAX_WIDTH + 2] = { {BLANK} };

//{
//	//      0         1			2		  3			4		   5		6		  7
//	//012345678901234567890123456789012345678901234567890123456789012345678901234567890"
//                                        1
//	 "############################################     ###############################\n",//0
//	 "#                                                                              #\n",//1
//	 "#  ####      #######################    ##########                  ############\n",//2
//	 "#  ####      #######################    ########################               #\n",//3
//	 "#            ###                        ########         ##         ############\n", //4
//	 "################  ###############################   ############################\n",//5
//	 "################      ############################ #############################\n",//6
//	 "#                                                                              #\n",//7
//	 "#################    #############             #################################\n",//8
//	 "#################    #############             #################################\n",//9
//	 "                                                                                \n",//10
//	 "####       ######################    ########################             ######\n",//11
//	 "#####                #########            ###################   ######         #\n",//12
//	 "#################################   #########################   ######         #\n",//13
//	 "#                                                           #   ######         #\n",//14
//	 "########    #######  ###################################        ################\n",//15
//	 "######        #####  #########        ##################   ##                  #\n",//16
//	 "###################  ##########      ###################   ##   #########   ####\n",//17
//	 "#                                ##                        ##                  #\n",//18
//	 "############################################     ###############################\n" //19 
//};

GameBoard::GameBoard() {
	//fillBreadCrumbs(false);
	initBoard();
}
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
void GameBoard::getGhostsPos(Point*& pos, int& size)
{
	pos = ghostsInitPos;
	size = ghost_num;
}


void GameBoard::getAllScreenFile()
{


	string workingDirectory = std::filesystem::current_path().string();
	cout << workingDirectory;
	for (const auto& entry : directory_iterator(std::filesystem::current_path()))
	{
		string fileExtension = entry.path().filename().extension().string();
		if(fileExtension==".screen")
			cout << entry.path().filename().string() << endl;
	}
		

}
void GameBoard::print()
{
	clearScreen();
	
	
	{

		for (int i = 0; i < height; i++)
		{

			for (int j = 0; j < width+1 && board[i][j] != '\0'; j++)
			{

				switch (board[i][j])
				{
				case WALL:
					if (Game::active_color) 
						{ setTextColor(Color::LIGHTCYAN); }
					_putch(board[i][j]);
					break;
				case BREADCRUMBS:
					if (Game::active_color)
						{ setTextColor(Color::LIGHTGREY); }
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
	}
	
	if (Game::active_color)
		setTextColor(Color::LIGHTGREY);
	/*cout << "pacman pos(" << pacmanInitPos.getX() << ',' << pacmanInitPos.getY() << ')' << endl
		<< "ghost 1 pos(" << ghostsInitPos[0].getX() << ',' << ghostsInitPos[0].getY() << ')' << endl
		<< "ghost 2 pos(" << ghostsInitPos[1].getX() << ',' << ghostsInitPos[1].getY() << ')' << endl
		<< "ghost 3 pos(" << ghostsInitPos[2].getX() << ',' << ghostsInitPos[2].getY() << ')' << endl
		<< "ghost 4 pos(" << ghostsInitPos[3].getX() << ',' << ghostsInitPos[3].getY() << ')' << endl
		<< "legend 1 pos(" << legendPos.getX() << ',' << legendPos.getY() << ')' << endl;*/
	gotoxy(legendPos.getX(), legendPos.getY());
	cout << "Lives:";
	gotoxy(legendPos.getX(), legendPos.getY() + 1);
	cout << "Score:";

	
}


void GameBoard::clearLegendAera()
{
	int x = legendPos.getX();
	int y = legendPos.getY();

		

	for (int row = y; row < y +3&&row<MAX_HEIGHT; row++)
		for (int col = x; col < x+20 &&col<MAX_WIDTH; col++)
		{
			board[row][col] = EMPTY;
				
			

		}


}

void GameBoard::loadBoardFromFile(string fileName)
{
	getAllScreenFile();
	width = height = 0;
	initBoard();
	ifstream boardFile(fileName);
	//print();
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

					//board[row][lineLen] = BLANK;
					board[row][width] = '\n';
					board[row][width + 1] = '\0';
				
			}
			height = row ;
			
			//print();




			for (int row = 0; row < height; row++)
				for (int col = 0; col < width; col++)
				{

					switch (board[row][col])
					{
					case PACMAN:
						pacmanInitPos = { col,row };
						board[row][col] = BLANK;
						break;
					case GHOST:
						if (ghost_num < Game::GHOSTS::MAX_GHOSTS)
						{
							ghostsInitPos[ghost_num] = { col,row };
							ghost_num++;//logical size of ghostsInitPos[]
						}
						board[row][col] = BLANK;
						break;
					case LEGEND:
						legendPos = { col,row };
						break;
					case WALL:;
					case EMPTY:break;
					default:
						board[row][col] = BLANK;

					}



				}
		
//			print();
			clearLegendAera();


			int yLegend = legendPos.getY();
			/*the legend position in the last 2 board row,increase height of board game*/
			if (yLegend + 3 > height && yLegend + 3 <= MAX_HEIGHT)
			{
				height = yLegend + 3;
				board[yLegend + 1][width] = '\n';
				board[yLegend + 1][width + 1] = '\0';
				board[yLegend + 2][width] = '\n';
				board[yLegend + 2][width + 1] = '\0';
			}
		}
	else
		cout << "Faild to Open file";
		//
		//print();
		fillBreadCrumbs(false);

		//print();
	
		//cout << endl;


}
int GameBoard::copyLineToRow(const string& src, char* row, int size) 
{
	int len;
	for (len = 0; len < size && len < src.length(); len++)
		row[len] = src[len];

	return len;

}
void GameBoard::saveSpaceLegendFirstLine() {

	for (int i = 0; i < width; i++)
		if (board[0][i] == LEGEND)
		{
			board[0][width] = BLANK;
			if (i + 20 > MAX_WIDTH)
				width = MAX_WIDTH;
			else {
				width = i + 20;


			}


		}

}
void GameBoard::printScoreToScreen(const int& score)
{
	
	gotoxy(legendPos.getX()+7, legendPos.getY()+1);
	cout << score;
}
void GameBoard::printLivesToScreen(const int& lives)
{
	

	
	gotoxy(legendPos.getX()+7, legendPos.getY());
	cout << lives;
}
//the erase the invisible breadcrumbs in Pacman init position
void GameBoard::removeBreadCrumbsInPacmanPos(const Point& pos)
{
	int xPos = pos.getX();
	int yPos = pos.getY();
	numOfBreadCrumbs--;
	clearBreadcumbsInBoard(xPos, yPos);
}
void GameBoard::clearBreadcumbsInBoard(int x, int y)
{
	board[y][x] = BLANK;
}
void GameBoard::resetBoard()
{
	fillBreadCrumbs(true);
}
void GameBoard::fillBreadCrumbs(bool isGameReset)
{
	for (int row = 1; row < height-1; row++)
	{
		for (int col = 1; col < width-1; col++)
			if (board[row][col] == BLANK)
			{
				board[row][col] = BREADCRUMBS;
				if (!isGameReset)//in case the game only reset board,dont increase the number of Bread Crumbs
					numOfBreadCrumbs++;
			}
	}
}
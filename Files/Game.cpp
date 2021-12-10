
// Constructor
#include <ctime>
#include "Game.h"
#include "GameBoard.h"
#include "GameMenu.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Color.h"

int Game::gameSpeed = NORMAL_GAME_SPEED;
GameBoard Game::_board;
bool Game::active_color = false;
Game::Game() : _moveCounter(MOVE_COUNTER_ROUNDS)
{
    srand((unsigned int)time(NULL));
    _arrowKeys[DIRECTION::UP][0] = w; // UP
    _arrowKeys[DIRECTION::UP][1] = W; // UP
    _arrowKeys[DIRECTION::DOWN][0] = x; // DOWN
    _arrowKeys[DIRECTION::DOWN][1] = X; // DOWN
    _arrowKeys[DIRECTION::LEFT][0] = a; // LEFT
    _arrowKeys[DIRECTION::LEFT][1] = A; // LEFT
    _arrowKeys[DIRECTION::RIGHT][0] = d; // RIGHT
    _arrowKeys[DIRECTION::RIGHT][1] = D; // RIGHT
    _arrowKeys[DIRECTION::STAY][0] = s; // STAY
    _arrowKeys[DIRECTION::STAY][1] = S; // STAY
    _board.removeBreadCrumbsInPacmanPos(_pacman.getPosition());
    

}
 void Game::gameLoop()
{
    bool isGamePause = false;
    char key = 20;
    bool exitGame = false;
    
    _board.print();
    
    _board.printLivesToScreen(_pacman.getLives());
    _board.printScoreToScreen(_pacman.getScore());
   resetAllCharactersToInitPos();//for first draw

    while (gameMenu.getCurrGameOption() !=gameMenu.OPTION::EXIT&&_pacman.getLives() && _pacman.getScore() < _board.getNumberOfBreadCrumbs())
    {
        if (_kbhit())//user hit a key in key board
        {
            key = _getch();
            if (key == ESC)
                pauseMode(isGamePause);
            else if ((key == 'G' || key == 'g') && isGamePause)//if the game paused and user wants to get out.
               gameMenu.setGameOption(gameMenu.OPTION::EXIT);

            else
                tempDir =convertKeyToDirection(key);//convert current key to direction,-1 for invalid key

        }

        if (isValidDirection(tempDir, _pacman.getPosition(), ALLOW_TUNNEL, ALLOW_STAY))
            pacmanDir = tempDir;

        checkPacmanHitsGhosts();

        if (isValidDirection(pacmanDir, _pacman.getPosition(), ALLOW_TUNNEL, ALLOW_STAY) && pacmanDir != STAY && !isGamePause)
        {
            _pacman.movePacman(pacmanDir);
            int xPacmanPos = _pacman.getPosition().getX();
            int yPacmanPos = _pacman.getPosition().getY();
            if (_board.getCurrBoardChar(xPacmanPos, yPacmanPos) == _board.BREADCRUMBS)
            {
                _board.clearBreadcumbsInBoard(xPacmanPos, yPacmanPos);
                if (active_color)
                    setTextColor(Color::LIGHTGREY);
                _board.printLivesToScreen(_pacman.getLives());
                _board.printScoreToScreen(_pacman.getAndUpdateScore());
            }
        }

        checkPacmanHitsGhosts();

        if (!isGamePause)
        {
            moveGhosts();
        }

        Sleep(gameSpeed);
        _moveCounter++;

    }
    if (gameMenu.getCurrGameOption() != gameMenu.OPTION::EXIT)
    {
        resetGame();
     
     
    }
       
}


 void Game::resetGame()
 {


     resetAllCharactersToInitPos();
     _board.clearScreen();
     gameMenu.gameEnd(_pacman.getLives());
     _moveCounter = MOVE_COUNTER_ROUNDS;
     _pacman.resetPacmanData();
     _board.resetBoard();
}
 void Game::getCreaturesInitPos()
 {
     Point* ghostTemp;
    
     
     _board.getGhostsPos(ghostTemp, ghostsSize);
     PACMAN_START_POS = _board.getPacmanPos();

     for (int i = 0; i < ghostsSize; i++)
         GHOSTS_START_POS[i] = ghostTemp[i];
     
     /*cout << "pacman pos(" << PACMAN_START_POS.getX() << ',' << PACMAN_START_POS.getY() << ')' << endl
        << "ghost 1 pos(" << GHOSTS_START_POS[0].getX() << ',' << GHOSTS_START_POS[0].getY() << ')' << endl
        << "ghost 2 pos(" << GHOSTS_START_POS[1].getX() << ',' << GHOSTS_START_POS[1].getY() << ')' << endl
        << "ghost 3 pos(" << GHOSTS_START_POS[2].getX() << ',' << GHOSTS_START_POS[2].getY() << ')' << endl
        << "ghost 4 pos(" << GHOSTS_START_POS[3].getX() << ',' << GHOSTS_START_POS[3].getY() << ')' << endl;*/

 }
void Game::start() { 
   


    _board.loadBoardFromFile("BoardTest.screen");//"BoardTest.txt"
    getCreaturesInitPos();
    while (gameMenu.getCurrGameOption() != gameMenu.OPTION::EXIT)
    {
        bool toRunGame = false;

        gameMenu.Print(toRunGame);
        if (toRunGame)
            gameLoop();

        _moveCounter = MOVE_COUNTER_ROUNDS;

        _pacman.resetPacmanData();
        _board.resetBoard();

    }

}


void Game::resetAllCharactersToInitPos()
{

    Point oldPos;
    pacmanDir = NOT_INIT;
    tempDir = NOT_INIT;
    oldPos = _pacman.getPosition();
    _pacman.setPosition(PACMAN_START_POS);
    _pacman.Draw(oldPos,active_color);
 
    
    for (int i = 0; i < ghostsSize; i++)
    {

        oldPos = _ghosts[i].getPosition();
        
        _ghosts[i].setPosition(GHOSTS_START_POS[i]);
        _ghosts[i].Draw(oldPos);

    }
}

void Game::checkPacmanHitsGhosts() // Checks if pacman hits the ghosts, returning true in case he does.
{
    int x = _pacman.getPosition().getX();
    int y = _pacman.getPosition().getY();
    for (int i = 0; i < ghostsSize; i++)
    {
        if (x == _ghosts[i].getPosition().getX() && y == _ghosts[i].getPosition().getY())
        {
            _board.printLivesToScreen(_pacman.getAndUpdateLife());
            resetAllCharactersToInitPos();
            return;
        }

    }

}

void Game::moveGhosts() // Updates ghosts' moves
{


    Point oldPos;
    for (int i = 0; i < ghostsSize; i++)
    {
        if (_moveCounter == MOVE_COUNTER_ROUNDS || !isValidDirection(_ghosts[i].getDirection(), _ghosts[i].getPosition(), !ALLOW_TUNNEL, !ALLOW_STAY))
        {
            _ghosts[i].pickDirection();
            _moveCounter = 0; // set moveCounter
        }
        if (_ghosts[i].getMovement()) // IF THE GHOST CAN MOVE IN THIS ROUND
        {
            _ghosts[i].move();
        }
        if (active_color)
            setTextColor(Color::YELLOW);
        _ghosts[i].setIsMovement(_ghosts[i].getMovement()^ true);

    }
}
void Game::pauseMode(bool& gamePause)
{
    if (!gamePause)//switch beetween pause mode
    {
        gotoxy(20, GameBoard::MAX_HEIGHT + 2);
        cout << "Game Pause! press ESC to continue or g (exit game) ......";
        gamePause = true;
    }
    else
    {
        gotoxy(20, GameBoard::MAX_HEIGHT + 2);
        cout << "                                                                   ";;
        gamePause = false;
    }



}
bool Game::isValidDirection(int key, const Point& currPos, bool allowedTunnel, bool allowStay)
{
    
    int xPos = currPos.getX();
    int yPos = currPos.getY();
    GameBoard tmpBoard = _board;
    if ((key ==UP && (_board.getCurrBoardChar(xPos, yPos - 1) != GameBoard::WALL)))
    {
        if (allowedTunnel)
            return true;
        else if (yPos - 1 > 0)
            return true;
    }
    else if (key == DOWN && (_board.getCurrBoardChar(xPos, yPos + 1) != GameBoard::WALL))
    {
        if (allowedTunnel)
            return true;
        else if (yPos + 1 < _board.getBoardHeight() - 1)
            return true;
    }
    else if (key == LEFT && (_board.getCurrBoardChar(xPos - 1, yPos) != GameBoard::WALL))
    {
        if (allowedTunnel)
            return true;
        else if (xPos - 1 > 0)
            return true;
    }
    else if (key == RIGHT && (_board.getCurrBoardChar(xPos + 1, yPos) != GameBoard::WALL))
    {
        if (allowedTunnel)
            return true;
        else if (xPos + 1 < _board.getBoardWidth() - 1)
            return true;

    }
    else if (allowStay && key == STAY)
        return true;

    return false;
}
int Game::convertKeyToDirection(char key)
{
    for (int i = 0; i < DIRECTION::SIZE; i++)
    {
        if (key == _arrowKeys[i][0] || key == _arrowKeys[i][1])
            return i;
    }
    return NOT_INIT;
}



void Game::setGameSpeed(int speed)
{
    gameSpeed = speed;
}





//void Game::gameMenu()
//{
//    
//    gameOption = NOT_INIT;
//
//    while (gameOption ==OPTION::NOT_INIT)
//    {
//
//        GameBoard::clearScreen();
//
//        gameOption = getGameMenuOptionFromUser();
//        switch (gameOption)
//        {
//        case OPTION::START:
//           gameLoop();
//            break;
//        case OPTION::WITH_COLORS:
//            active_color = true;
//            gameLoop();
//            break;
//        case OPTION::CHANGE_GAME_SPEED:
//            gameSpeedMenu();
//            break;
//        case OPTION::HOW_TO_PLAY:
//            howToPlay();
//            break;
//        case OPTION::EXIT:
//            break;
//
//        default:;
//        }
//        if (gameOption != OPTION::EXIT)
//            gameOption = OPTION::NOT_INIT;//for reset game menu
//    }
////}
//int  Game::getGameMenuOptionFromUser()
//{
//    char userChoice = NOT_INIT;
//    cout << "#############################\n"
//        << "#1  -Start The Game         #\n"
//        << "#2  -Start with colors      #\n"
//        << "#3  -Change game speed      #\n"
//        << "#8  -How To Play            #\n"
//        << "#9  -Exit                   #\n"
//        << "#############################\n";
//
//    userChoice = _getch();
//
//
//    while ((userChoice > '9' || userChoice < '8') && (userChoice < '1' || userChoice>'3'))
//    {
//        gotoxy(5, 10);
//        clog << "Not valid game menu option\nPlease enter number between 1,2,3,8 or 9" << endl;
//        gotoxy(0, 0);
//        userChoice = _getch();
//    }
//
//
//
//    if (Game::active_color)
//        setTextColor(Color::YELLOW);
//    GameBoard::clearScreen();
//    cout << " __   _     __       _  _     _    _                " << endl;
//    cout << "|__) /_\\   /    __  / \\/ \\   /_\\  | \\ |        " << endl;
//    cout << "|   /   \\  \\__     /      \\ /   \\ |  \\|        " << endl << endl;
//    if (Game::active_color)
//        setTextColor(Color::LIGHTGREY);
//
//    Sleep(500);
//
//
//
//    return userChoice - '0';
//}
//void Game::howToPlay()
//{
//    GameBoard::clearScreen();
//    cout << "the pacman(@ in screen) need to eat all the breadcrumbs \n"
//        << "in the board without touching the ghost($ in screen)\n"
//        << "the pacman will continue moving until you hit:\n"
//        << "W-for go UP\nA-for go LEFT\nD-for go RIGHT\nX-for go DOWN\nS-to stay in position"
//        << "\n\n\npress any key to return game menu" << endl;
//    while (!_kbhit()) {}//wait for user input
//    char temp = _getch();//clean buffer
//}
//void Game::gameSpeedMenu()
//{
//    GameBoard::clearScreen();
//    cout << "#1 FAST SPEED" << endl
//        << "#2 REGULAR SPEED" << endl
//        << "#3 SLOW SPEED" << endl;
//    char userChoice = Game::NOT_INIT;
//    do
//    {
//        userChoice = _getch();
//        gotoxy(5, 10);
//        clog << "Not valid speed option\nPlease enter number between 1,2,3" << endl;
//        gotoxy(0, 0);
//    } while (userChoice < '1' || userChoice>'3');
//    switch (userChoice)
//    {
//    case FAST:
//       gameSpeed=FAST_GAME_SPEED;
//        break;
//    case NORMAL:
//        gameSpeed=NORMAL_GAME_SPEED;
//        break;
//        break;
//    case SLOW:
//        gameSpeed = SLOW_GAME_SPEED;
//        break;
//    default:;
//    }
//
//}

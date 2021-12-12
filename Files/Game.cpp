
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


    while (gameMenu.getCurrGameOption() !=gameMenu.OPTION::EXIT&&_pacman.getLives() && _board.getSumBreadCrumbEated() < _board.getSumOfBreadCrumbsInBoard())//todo:
    {
        if (_kbhit())//user hit a key in key board
        {
            key = _getch();
            if (key == ESC)
                pauseMode(isGamePause);
            else if ((key == 'G' || key == 'g') && isGamePause)//if the game paused and user wants to get out.
            {
                gameMenu.setGameOption(gameMenu.OPTION::EXIT);
                toRunGame = false;
                return;
            }

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
    if (_pacman.getLives() == 0)
        toRunGame = false;
}

//
// void Game::resetCurrGameSession()
// {
//
//
//     resetAllCharactersToInitPos();
//     _board.clearScreen();
//   
//     _moveCounter = MOVE_COUNTER_ROUNDS;
//     _pacman.resetPacmanData();
//    
//     _board.resetBoard();
//}
 void Game::getCreaturesInitPos()
 {
     Point* ghostsTemp;//pointer to static array,no need to release
    
     
     _board.getGhostsPos(ghostsTemp, ghostsSize);
     PACMAN_START_POS = _board.getPacmanPos();
     _board.removeBreadCrumbsInPacmanPos(PACMAN_START_POS);
     for (int i = 0; i < ghostsSize; i++)
         GHOSTS_START_POS[i] = ghostsTemp[i];
     
 }
void Game::start() { 
    _board.getAllScreenFile();
        while (gameMenu.getCurrGameOption() != gameMenu.OPTION::EXIT)
        {
            _board.resetToFirstScreenFileName();
             toRunGame = false;
            gameMenu.Print(toRunGame);

            while (toRunGame&&!_board.isScreenFileNameListEmpty())
            {
                _board.loadBoardFromFile(_board.getNextScreenFileName());
     
                getCreaturesInitPos();
            
                gameLoop();
           }
      
            if (gameMenu.getCurrGameOption() != gameMenu.OPTION::EXIT)
            {
                gameMenu.gameEnd(_pacman.getLives());
                _moveCounter = MOVE_COUNTER_ROUNDS;
                _pacman.resetPacmanData();
               //_board.resetBoard();
            }
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
        if (yPos - 1 > 0)
            return true;
        else if (allowedTunnel&& (_board.getCurrBoardChar(xPos, _board.getBoardHeight()-1) != GameBoard::WALL))
            return true;
    }
    else if (key == DOWN && (_board.getCurrBoardChar(xPos, yPos + 1) != GameBoard::WALL))
    {
        if (yPos + 1 < _board.getBoardHeight() - 1)
            return true;
        else if (allowedTunnel && (_board.getCurrBoardChar(xPos, 0) != GameBoard::WALL))
            return true;
    }
    else if (key == LEFT && (_board.getCurrBoardChar(xPos - 1, yPos) != GameBoard::WALL))
    {
        if (xPos - 1 > 0)
            return true;
        else if (allowedTunnel && (_board.getCurrBoardChar(_board.getBoardWidth()-1, yPos) != GameBoard::WALL))
            return true;
    }
    else if (key == RIGHT && (_board.getCurrBoardChar(xPos+1, yPos) != GameBoard::WALL))
    {
        if (xPos + 1 < _board.getBoardWidth() - 1) 
            return true;
        else if (allowedTunnel&& (_board.getCurrBoardChar(0, yPos) != GameBoard::WALL))
            return true;

    }
    else if (allowStay && key == STAY)
        return true;

    return false;
}
int Game::convertKeyToDirection(char key)
{
    for (int dir = 0; dir < DIRECTION::SIZE; dir++)
    {
        if (key == _arrowKeys[dir][0] || key == _arrowKeys[dir][1])
            return dir;
    }
    return NOT_INIT;
}



void Game::setGameSpeed(int speed)
{
    gameSpeed = speed;
}





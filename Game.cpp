
// Constructor
#include <ctime>
#include <algorithm>
#include "Game.h"
#include "GameBoard.h"
#include "GameMenu.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Color.h"


short Game::_gameMode = GAME_MODE::SIMPLE;
int Game::gameSpeed = NORMAL_GAME_SPEED;
int Game::ghostsLevel = GameMenu::GHOST_TYPE::GOOD_GHOST_LEVEL;
int Game::ghostsSize = 0;
//int Game::ghostsLevel = GameMenu::GHOST_TYPE::GOOD_GHOST_LEVEL;


bool Game::active_color = false;
GameBoard Game::_board;
ExceptionsManager Game::excepMgr;
Game::Game() : _moveGhostCounter(MOVE_COUNTER_ROUNDS), _fruitMoveCounter(MOVE_COUNTER_ROUNDS)
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

void Game::setGameSpeed(int speed)
{
    gameSpeed = speed;
}

void Game::setGhostsLevel(char option)
{

    ghostsLevel = option;
}
void Game::start() {

    if (invalidArguments)
        return;

    while (gameMenu.getCurrGameOption() != gameMenu.OPTION::EXIT)
    {

     
        toRunGame = false;
        gameMenu.Print(toRunGame);
        string boardFileName = gameMenu.getBoardFileName();
        if (gameMenu.getCurrGameOption() == GameMenu::LOAD_SPECIFIC_SCREEN && !boardFileName.empty())
            _board.addScreenFileName(boardFileName);
        else
            _board.getAllScreenFile();

        atLeast1BoardFinish = false;
        _board.resetToFirstScreenFileName();
        if (!_board.isScreenFileNameListEmpty())
        {
            while (toRunGame && !_board.isScreenFileNameListEmpty())
            {
                try {
                    string currBoardFileName = _board.getNextScreenFileName();
                    _board.loadBoardFromFile(currBoardFileName);
                    getCreaturesInitPos();
                    openStepsAndResultFiles(currBoardFileName);
                    gameLoop();
                  
                }
                catch (ExceptionsManager* mngr)
                {
                    if (gameMenu.getCurrGameOption() != gameMenu.OPTION::EXIT)
                    {
                        mngr->printAllMsg();
                        cout << "The game will skip this board and continue to next board screen" << endl;
                        std::cout << std::endl << std::endl;
                        system("pause");
                        GameBoard::clearScreen();
                    }

                }
            }

            if (gameMenu.getCurrGameOption() != gameMenu.OPTION::EXIT)
            {
                _board.clearFileNameList();
                gameMenu.gameEnd(_pacman.getLives(), atLeast1BoardFinish);
                _moveGhostCounter = MOVE_COUNTER_ROUNDS;
                _pacman.resetPacmanData();

            }
            if (Game::active_color)
            {
                setTextColor(Color::WHITE);
            }
            active_color = false;

        }
        else
        {
            cout<<"ERROR!not found any screen board file, \n please add board screen file to working directory!"<<endl;
            system("pause");
        }

    }

}
 void Game::gameLoop()
{
    bool isGamePause = false;
    char key = 20;
    bool exitGame = false;
    stepCounter = 1;
   
    _board.print();
    _board.printLivesToScreen(_pacman.getLives());
    _board.printScoreToScreen(_pacman.getScore());
   resetAllCreaturesToInitPos();//for first draw

    for (int i = 0; i < ghostsSize; i++)//set ghosts level according to the user's input
        _ghosts[i].setMoveStrategy(ghostsLevel);
    _fruit.setMoveStrategy(GameMenu::GHOST_TYPE::NOVICE_GHOST_LEVEL);
   
  
    while ( (gameMenu.getCurrGameOption() !=gameMenu.OPTION::EXIT) && _pacman.getLives() && ( _board.getSumOfBreadCrumbsInBoard()>0) )
    {
        stepsString = STEPS_FORMAT;

        checkForUserInput(isGamePause);
        if (!toRunGame)
            return;

        
        if (isValidDirection(_pacman.getDirection(), _pacman.getPosition(), ALLOW_TUNNEL, ALLOW_STAY) && _pacman.getDirection() != DIRECTION::STAY && !isGamePause)
        {
            _pacman.movePacman();
            checkPacmanHitsGhosts();
            checkPacmanEatFruit();
            int xPacmanPos = _pacman.getPosition().getX();
            int yPacmanPos = _pacman.getPosition().getY();
            if (_board.getCurrBoardChar(xPacmanPos, yPacmanPos) == _board.BREADCRUMBS)
            {
                _board.clearBreadcumbsInBoard(xPacmanPos, yPacmanPos);
                 _board.printLivesToScreen(_pacman.getLives());
                 _board.printScoreToScreen(_pacman.getAndUpdateScore());
            }
        }
        
        if (!isGamePause)
        {
           
            randomFruit();
            moveGhosts();
            stepCounter++;
            saveStepsToFile();
        }
        if(_gameMode==GAME_MODE::LOAD)
           Sleep(FAST_GAME_SPEED /2);
        else if (_gameMode != GAME_MODE::LOAD_SILENTLY)
            Sleep(gameSpeed);

        
    }

    atLeast1BoardFinish = true;
    if (_pacman.getLives() == 0)
    {
        toRunGame = false;
        saveAndCheckResultFile("Game Over!!!", true);
    }
    else
        saveAndCheckResultFile("board passed!", true);
}


 void Game::getCreaturesInitPos()
 {
     Point* ghostsTemp;//pointer to static array,no need to release
    
     _fruit.resetFruit();
     _board.getGhostsPos(ghostsTemp, ghostsSize);
     PACMAN_START_POS = _board.getPacmanPos();
     _board.removeBreadCrumbsInPacmanPos(PACMAN_START_POS);
     for (int i = 0; i < ghostsSize; i++)
         GHOSTS_START_POS[i] = ghostsTemp[i];
     
 }


void Game::debugGhost(int offset,string fun) {
    static int inOff = 0;
    gotoxy(_board.getBoardWidth() + 3,0+offset+ inOff);
    cout << fun;
    for (int i = 0; i < ghostsSize; i++)
    {
        gotoxy(_board.getBoardWidth() + 8, i + offset);
        cout << "ghost " << i + 1 << _ghosts[i].getPosition() << endl;
    }
       
    inOff = +ghostsSize;
}


void Game::resetAllCreaturesToInitPos()
{
    _fruit.disappearFruit();
    Point oldPos;
   
    tempDir = NOT_INIT;

    for (int i = 0; i < ghostsSize; i++)
    {

        oldPos = _ghosts[i].getPosition();

        _ghosts[i].setPosition(GHOSTS_START_POS[i]);

        _ghosts[i].Draw(oldPos,_pacman.getPosition());

    }
    oldPos = _pacman.getPosition();
    _pacman.setDirection(DIRECTION::STAY);
    _pacman.setPosition(PACMAN_START_POS);
    _pacman.Draw(oldPos);
 
    
  
}

void Game::checkPacmanHitsGhosts() // Checks if pacman hits the ghosts, returning true in case he does.
{

    for (int i = 0; i < ghostsSize; i++)
    {
        if (_pacman.getPosition()== _ghosts[i].getPosition())
        {
            saveAndCheckResultFile("pacman died", false);
            _board.printLivesToScreen(_pacman.getAndUpdateLife());
            resetAllCreaturesToInitPos();
            return;
        }

    }

}

void Game::moveGhosts() // Updates ghosts' moves
{

    Point oldPos;
    for (int i = 0; i < ghostsSize; i++)
    {
        if (_gameMode == GAME_MODE::SAVE || _gameMode == GAME_MODE::SIMPLE)
        {
            if (ghostsLevel == GameMenu::GHOST_TYPE::NOVICE_GHOST_LEVEL)//change direction only every 10 rounds,unless it's illegal to stay in the same direction.
            {
                if (_moveGhostCounter == MOVE_COUNTER_ROUNDS || !isValidDirection(_ghosts[i].getDirection(), _ghosts[i].getPosition(), !ALLOW_TUNNEL, !ALLOW_STAY))
                { _ghosts[i].getMoveStrategy()->pickDirection(_pacman.getPosition(), _ghosts+i,i);
                    _moveGhostCounter = 0; // set moveCounter
                }
                
            }
            else
            {
                _ghosts[i].getMoveStrategy()->pickDirection(_pacman.getPosition(), _ghosts,i);

            }
        }
       
        if (_ghosts[i].getMovement()) // IF THE GHOST CAN MOVE IN THIS ROUND
        {
            if (_gameMode == GAME_MODE::SAVE)
                stepsString[STEPS_INDEX::GHOSTS + i * 5] = directionMap[_ghosts[i].getDirection()];
            else if (_gameMode == GAME_MODE::LOAD || _gameMode == GAME_MODE::LOAD_SILENTLY)
            {
                _ghosts[i].setDirection(convertDirFromFile(stepsString[STEPS_INDEX::GHOSTS + i * 5], "ghost number " + std::to_string(i + 1)));
                if (!isValidDirection(_ghosts[i].getDirection(), _ghosts[i].getPosition(), !ALLOW_TUNNEL, !ALLOW_STAY))
                {
                    invalidDirectionInStepFileException(stepsString[STEPS_INDEX::GHOSTS + i * 5], "ghost number " + std::to_string(i + 1));
                }
            }
            _ghosts[i].move(_pacman.getPosition());

        }

        if (i == 0 && _ghosts[0].getMovement())
        {
            _moveGhostCounter++;
        }
        _ghosts[i].setIsMovement(_ghosts[i].getMovement() ^ true);    
        checkPacmanHitsGhosts();
        checkFruitHitGhost();
        
        }
    }


bool Game::isValidDirection(int key, const Point& currPos, bool allowedTunnel, bool allowStay)
{
    
    int xPos = currPos.getX();
    int yPos = currPos.getY();
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
    else if (allowStay && key == DIRECTION::STAY)
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




void Game::getNewValidRandomPositionFruit()
{
  
    Point randomPosition;
    do
    {
        randomPosition.setX(1 + rand() % (_board.getBoardWidth() - 3));
        randomPosition.setY(1 + rand() % (_board.getBoardHeight() - 3));


    } while ((GameBoard::getCurrBoardChar(randomPosition.getX(), randomPosition.getY()) == GameBoard::WALL) ||
                    (_board.checkIfLegendAera(randomPosition))|| (randomPosition ==_pacman.getPosition())||randomPosition==_fruit.getOldPos());

    _fruit.setPosition(randomPosition);
}
void Game::UpdateFruitMoves()
{
   

    if (_fruitMoveCounter == FRUIT::FRUIT_MAX_MOVES || !isValidDirection(_fruit.getDirection(), _fruit.getPosition(), !ALLOW_TUNNEL, !ALLOW_STAY))
    {

        _fruit.getMoveStrategy()->pickDirection(_pacman.getPosition(), &_fruit,0);
        _fruitMoveCounter = 0; // set moveCounter
    }
    if (_fruit.getMovement()) // IF THE FRUIT CAN MOVE IN THIS ROUND
    {
        _fruitMoveCounter++;
        if (_gameMode == GAME_MODE::SAVE)
        {
            stepsString[STEPS_INDEX::FRUIT_DIR] = directionMap[_fruit.getDirection()];
        }
        else if(_gameMode == GAME_MODE::LOAD_SILENTLY|| _gameMode == GAME_MODE::LOAD)
        {
            _fruit.setDirection(convertDirFromFile(stepsString[STEPS_INDEX::FRUIT_DIR], "fruit"));
            if (!isValidDirection(_fruit.getDirection(), _fruit.getPosition(), !ALLOW_TUNNEL, !ALLOW_STAY))
                invalidDirectionInStepFileException(stepsString[STEPS_INDEX::FRUIT_DIR], "fruit");

        }
       _fruit.move(_pacman.getPosition());
       checkFruitHitGhost();
       checkPacmanEatFruit();
    }


    _fruit.setIsMovement(_fruit.getMovement() ^ true);

}
void Game::checkPacmanEatFruit()
{
    if (_pacman.getPosition() == _fruit.getPosition())
    {
        _pacman.addFruitToScore(_fruit.getFigure());
        _board.printScoreToScreen(_pacman.getScore());
        _fruit.resetFruit();
     
    }


}

void Game::randomFruit()
{
    static int randomCounter = FRUIT::FRUIT_RANDOM_APRR;
    randomCounter -= 2;
    //  int randomNum = rand() % (FRUIT::FRUIT_RANDOM_APRR);
    if (_fruit.isOnScreen())
    {
   
        UpdateFruitMoves();//move fruit,change it's direction every 10 moves or if the direction is illigal 

        if (_fruit.checkTimeSpan() == 0)
        {
            _fruit.disappearFruit();
        }
        else
            _fruit.setTimeSpan(_fruit.checkTimeSpan() - 1);//decrease fruit time span by one each loop 
    }
    /* if fruit is not on screen, move counter countes
    the number of game loops and reset when it reaches 20,we randomly
        choose a number of movecounter that the fruit will appear on*/
    else if (_gameMode == GAME_MODE::LOAD || _gameMode == GAME_MODE::LOAD_SILENTLY|| rand() % (FRUIT::FRUIT_RANDOM_APRR) == randomCounter)
    {
        if (_gameMode == GAME_MODE::SAVE || _gameMode == GAME_MODE::SIMPLE)
        {
            _fruit.setFruitOnScreen(true);
            getNewValidRandomPositionFruit();
            if (_gameMode == GAME_MODE::SAVE)
            {
                Point fPos = _fruit.getPosition();
                stepsString[STEPS_INDEX::FRUIT_APP] = 't';
                stepsString[STEPS_INDEX::FRUIT_X] = (fPos.getX() / 10)+'0';
                stepsString[STEPS_INDEX::FRUIT_X + 1] = (fPos.getX() % 10 )+ '0';
                stepsString[STEPS_INDEX::FRUIT_Y] = (fPos.getY()/10 ) + '0';
                stepsString[STEPS_INDEX::FRUIT_Y + 1] = (fPos.getY() % 10)+'0';
            }
        }
        else if(stepsString[STEPS_INDEX::FRUIT_APP] == 't')//check the current step for create the fruit in the same time it was in save mode
        {
            int xPos = (stepsString[STEPS_INDEX::FRUIT_X] - '0') * 10+ (stepsString[STEPS_INDEX::FRUIT_X+1] - '0');
            int yPos = (stepsString[STEPS_INDEX::FRUIT_Y] - '0') * 10 + (stepsString[STEPS_INDEX::FRUIT_Y + 1] - '0');
            _fruit.setFruitOnScreen(true);
            _fruit.setPosition({ xPos,yPos });
        }
    
        if (_fruit.isOnScreen())
        {
            _fruit.newFigure(stepsString,stepsFileName,stepCounter);
            _fruit.Draw(_fruit.getPosition(), _pacman.getPosition());
            _fruit.setTimeSpan(_fruit.FRUIT_TIME_SPAN);
            _fruit.setIsMovement(true);
        }
    }

    if (randomCounter ==0 )
        randomCounter = FRUIT::FRUIT_RANDOM_APRR;
 
}

void Game::checkFruitHitGhost()
{
 
    for (int i = 0; i < ghostsSize; i++)
    {
        if (_fruit.getPosition() == _ghosts[i].getPosition())
        {
            _fruit.resetFruit();
            if (_gameMode == GAME_MODE::SAVE)
                stepsString[STEPS_INDEX::FRUIT_APP] = 'f';

        }
    }
}

void Game::openStepsAndResultFiles(const string& screenFileName)
{
    if (_gameMode != GAME_MODE::SIMPLE)
    {
        size_t extIndex = screenFileName.find_last_of(".");
        screenFileNameOnly = screenFileName.substr(0, extIndex);

        stepsFileName = screenFileNameOnly + STEPS_FILE_EXT;
        resultFileName = screenFileNameOnly + RESULT_FILE_EXT;
        if (stepsFile.is_open())
            stepsFile.close();
        if (resultFile.is_open())
            resultFile.close();
        if (_gameMode == GAME_MODE::SAVE)
        {
            stepsFile.open(stepsFileName, std::ios::out | std::ios::trunc);
            resultFile.open(resultFileName, std::ios::out | std::ios::trunc);
        }
        else if(_gameMode == GAME_MODE::LOAD_SILENTLY|| _gameMode == GAME_MODE::LOAD)
        {
            stepsFile.open(stepsFileName, std::ios::in);
            if (_gameMode == GAME_MODE::LOAD_SILENTLY)
                resultFile.open(resultFileName, std::ios::in);
        }
        
        if (stepsFile.fail())
            excepMgr.insertExcp("error when trying to open " + stepsFileName);
        if(_gameMode == GAME_MODE::LOAD_SILENTLY&&resultFile.fail())
            excepMgr.insertExcp("error when trying to open " + resultFileName);
        if ((_gameMode == GAME_MODE::LOAD_SILENTLY && resultFile.fail()) || stepsFile.fail())
            throw &excepMgr;
    }


}


void Game ::checkForUserInput( bool& isGamePause)
{
 
    char key = 20;
    
    if (_gameMode == GAME_MODE::SIMPLE || _gameMode == GAME_MODE::SAVE)
    {
        if (_kbhit())//user hit a key in key board
        {
            key = _getch();
            if (key == ESC)
                _board.printPauseMode(isGamePause, _pacman);

            else if ((key == 'G' || key == 'g') && isGamePause)//if the game paused and user wants to get out.
            {
             //   gameMenu.setGameOption(gameMenu.OPTION::EXIT);
                toRunGame = false;
                GameBoard::clearScreen();
                return;
            }
            else
            {
                tempDir = convertKeyToDirection(key);//convert current key to direction,-1 for invalid key
            }
        }

    }


    if (_gameMode == GAME_MODE::SAVE)
        stepsString[STEPS_INDEX::PACMAN] = directionMap[tempDir];
    else if (_gameMode == GAME_MODE::LOAD || _gameMode == GAME_MODE::LOAD_SILENTLY)
    {
        getNextGameSteps();
        tempDir =convertDirFromFile(stepsString[STEPS_INDEX::PACMAN],"pacman");
    }


    //although user not press any key ,check is last key currently is vaild
    if (isValidDirection(tempDir, _pacman.getPosition(), ALLOW_TUNNEL, ALLOW_STAY))
        _pacman.setDirection(tempDir);
}




void Game::saveStepsToFile()
{

    if (_gameMode == GAME_MODE::SAVE)
        stepsFile << stepsString;

}

void Game::getNextGameSteps()
{
 
    if(!stepsFile.eof())
        std::getline(stepsFile, stepsString);//load next steps of the creatures
    if(stepsFile.eof()|| stepsString.empty())
    { 
        throw  excepMgr.insertExcp("steps file '"+stepsFileName +"' incomplete, game not won or over\nnext game steps is missing in the file");
      
    }
}



int Game::convertDirFromFile(char dir, const string& creatureName)
{

    for (auto itr : directionMap)
    {
        if (itr.second == dir)
            return itr.first;
    }

    //step file have invalid direction,we send massge to user with bug details
    invalidDirectionInStepFileException(dir, creatureName);
    return NOT_INIT;//not use beacuse the Exception
}
void Game::invalidDirectionInStepFileException(char dir, const string& creatureName)
{   
    string msg = "invalid " + creatureName + " direction move '";
    msg.push_back(dir);
    msg += "' in steps file " + stepsFileName + " on line " + std::to_string(stepCounter);
    msg += "\nplease note as explain in file_format.txt only U,D,R,L,N is allow direction";
    throw excepMgr.insertExcp(msg);

}
void Game::saveAndCheckResultFile(const string& msg,bool boardEnded)
{

    if (_gameMode == GAME_MODE::SAVE)
        resultFile << stepCounter << ": " << msg << endl;
    else if (_gameMode == GAME_MODE::LOAD_SILENTLY)
    {
        string currMsg;
        int currStep;
        getCurrStepAndMsgFromResultFile(currStep, currMsg);
        
        if (resultFile.eof()|| currMsg != msg||(currMsg == msg && currStep!=stepCounter))
        {
            throw excepMgr.insertExcp( screenFileNameOnly+ " faild in test!");
        }
        else if (boardEnded)
        {
            cout << "the board "+ screenFileNameOnly+ " passed the test!!" << endl;
            Sleep(3000);
        }
       
    }
}
void Game::getCurrStepAndMsgFromResultFile(int& currStep, string& currMsg)
{


    string currResultLine;
    std::getline(resultFile, currResultLine);
    size_t stepNumberEnd = currResultLine.find_first_of(':');
    currStep = stoi(currResultLine.substr(0, stepNumberEnd));
    currMsg = currResultLine.substr(stepNumberEnd + 2);
}


void Game::getCommandLineArguments(int argc, char** argv)
{
    try {
        if (argc == 1)//there are not arguments,the default of the game is simple
            return;

        string pogramName = argv[0];
        if (argc > 3)
            throw Game::excepMgr.insertExcp("too many arguments!\nexiting from the program!....");
        if ((argc == 2 && strcmp(argv[1], commandArgumentMap[CMD_ARGUMENT::SAVE_ARG]) == 0)
            || ((argc == 3 && strcmp(argv[1], commandArgumentMap[CMD_ARGUMENT::SAVE_ARG]) == 0 &&strcmp(argv[2], commandArgumentMap[CMD_ARGUMENT::SILENT_ARG]) == 0)))
                    _gameMode = Game::GAME_MODE::SAVE;
        else if (argc == 2 && strcmp(argv[1], commandArgumentMap[CMD_ARGUMENT::LOAD_ARG]) == 0)
            _gameMode = Game::GAME_MODE::LOAD;
        else if (argc == 3 && strcmp(argv[1], commandArgumentMap[CMD_ARGUMENT::LOAD_ARG]) == 0 && strcmp(argv[2], commandArgumentMap[CMD_ARGUMENT::SILENT_ARG]) == 0)
            _gameMode = Game::GAME_MODE::LOAD_SILENTLY;
        else
            throw Game::excepMgr.insertExcp("invalid arguments!\nUsage:" + pogramName + " [-save][-load | -load -silent]\nexiting from the program!....");


    }
    catch (ExceptionsManager* mngr)
    {
        invalidArguments = true;
        mngr->printAllMsg();
       
   }
}

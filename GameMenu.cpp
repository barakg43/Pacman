#include "GameMenu.h"
#include "io_utils.h"
#include "GameBoard.h"
#include "Game.h"
#include "ExceptionsManager.h"
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;






void GameMenu::Print(bool& runGame)
{
    if (Game::getGameMode() == Game::GAME_MODE::LOAD || Game::getGameMode() == Game::GAME_MODE::LOAD_SILENTLY)
    {
        runGame = true;
        return;
    }

    while (!runGame)
    {
        GameBoard::clearScreen();

        gameOption = getGameMenuOptionFromUser();
        switch (gameOption)
        {
        case OPTION::START:
            runGame = true;
            break;
        case OPTION::WITH_COLORS:
            Game::active_color = true;
            runGame = true;
            break;
        case OPTION::CHANGE_GAME_SPEED:
            gameSpeedMenu();
            break;
        case OPTION::GHOSTS_MENU:
            ghostsLevelMenu();
            break;
        case OPTION::LOAD_SPECIFIC_SCREEN:
            try {
                checkIfBoardFileExist(runGame);
            }
       
            catch (ExceptionsManager* expMngr)
            {  
                expMngr->printAllMsg();   
                system("pause");
            }
            break;
        case OPTION::HOW_TO_PLAY:
            howToPlay();
            break;
        case OPTION::EXIT:
            return;
            break;

        default: break;
        }

        
    }
    printPacmanLogo();
   
    
}

int  GameMenu::getGameMenuOptionFromUser()
{
    char userChoice = NOT_INIT;
    cout << "##################################\n"
        << "#1  -Start The Game               #\n"
        << "#2  -Start with colors            #\n"
        << "#3  -Change game speed            #\n"
        << "#4  -Change ghosts Level          #\n"
        << "#5  -Load Specific Screen by Name #\n"
        << "#8  -How To Play                  #\n"
        << "#9  -Exit                         #\n"
        << "###################################\n";

    userChoice = _getch();


    while ((userChoice > OPTION::EXIT || userChoice < OPTION::HOW_TO_PLAY) && (userChoice < OPTION::START|| userChoice>OPTION::LOAD_SPECIFIC_SCREEN))
    {
        gotoxy(5, 10);
        clog << "Not valid game menu option\nPlease enter number between 1-5,8 or 9" << endl;
        gotoxy(0, 0);
        userChoice = _getch();
    }

    




    return userChoice;
}
void GameMenu::checkIfBoardFileExist(bool& runGame)
{

        bool fileIsGood = true;
        gotoxy(0, 10);
        cout << "Please enter screen board file name(*.screen):\n"
            << "                                                  \n"
            << "                                                  \n"
            << "                                                  \n"
            << "                                                  \n"
            << "                                                  \n"
            << "                                                  ";
        gotoxy(0, 11);
        cin >> boardfileName;
      
        ifstream file;
        file.open(boardfileName.c_str());
        if (file.fail())
        {
            Game::excepMgr.insertExcp("File not found!\nPlease enter existed file name!");
            fileIsGood = false;
        }

        if (GetFileExtension(boardfileName) != GameBoard::SCREEN_FILE_EXT)
        {
            Game::excepMgr.insertExcp("File Extension isn't " + GameBoard::SCREEN_FILE_EXT + " !!"
                + "\nPlease enter vaild file name with vaild extension!");
            fileIsGood = false;
        }
        if (!fileIsGood)
        {
            boardfileName = "";
            throw &Game::excepMgr;
        }
        else
            runGame = true;

 
}
    
   

string GameMenu::GetFileExtension(const string& FileName)
{
    if (FileName.find_last_of(".") != std::string::npos)
        return FileName.substr(FileName.find_last_of("."));
    return "";
}
void  GameMenu::printPacmanLogo() {


   
        GameBoard::clearScreen();
        if (Game::active_color)
            setTextColor(Color::YELLOW);
        cout << " __   _     __       _  _     _    _                " << endl
             << "|__) /_\\   /    __  / \\/ \\   /_\\  | \\ |        " << endl
             << "|   /   \\  \\__     /      \\ /   \\ |  \\|        " << endl << endl;
        if (Game::active_color)
            setTextColor(Color::LIGHTGREY);

        Sleep(500);
   
}
void GameMenu::howToPlay()
{
    GameBoard::clearScreen();
    cout << "the pacman(@ in screen) need to eat all the breadcrumbs \n"
        << "in the board without touching the ghost($ in screen)\n"
        << "the pacman will continue moving until you hit:\n"
        << "W-for go UP\nA-for go LEFT\nD-for go RIGHT\nX-for go DOWN\nS-to stay in position"
        << "\n\n\npress any key to return game menu" << endl;
    while (!_kbhit()) {}//wait for user input
    char temp = _getch();//clean buffer
}


void GameMenu::gameSpeedMenu()
{
    GameBoard::clearScreen();
    cout << "++++++++++++++++++++\n"
         << "+ 1 FAST SPEED     +\n" 
         << "+ 2 REGULAR SPEED  +\n" 
         << "+ 3 SLOW SPEED     +\n" 
         << "++++++++++++++++++++  " << endl;
    char userChoice = OPTION::NOT_INIT;
    userChoice = _getch();
     while(userChoice < FAST || userChoice > SLOW)
    {
      
        gotoxy(0, 5);
        clog << "Not valid speed option\nPlease enter number between 1,2,3" << endl;
        userChoice = _getch();
    } 
  
    switch (userChoice)
    {
    case FAST:
        Game::setGameSpeed(Game::FAST_GAME_SPEED);
        break;
    case NORMAL:
        Game::setGameSpeed(Game::NORMAL_GAME_SPEED);
        break;
    case SLOW:
        Game::setGameSpeed(Game::SLOW_GAME_SPEED);
        break;
    default:break;
    }

}
void GameMenu::ghostsLevelMenu()
{
    GameBoard::clearScreen();
    cout << "(a) BEST" << endl
         << "(b) GOOD" << endl
         << "(c) NOVICE" << endl;
    char userChoice = OPTION::NOT_INIT;
    do
    {
        userChoice = _getch();
        gotoxy(5, 10);
        clog << "Not valid speed option\nPlease enter valid letter a/b/c" << endl;
        gotoxy(0, 0);
    } while (userChoice < GHOST_TYPE::BEST_GHOST_LEVEL || userChoice>GHOST_TYPE::NOVICE_GHOST_LEVEL);
    switch (userChoice)
    {
    case GHOST_TYPE::BEST_GHOST_LEVEL:
        Game::setGhostsLevel(GHOST_TYPE::BEST_GHOST_LEVEL);
        break;
    case GHOST_TYPE::GOOD_GHOST_LEVEL:
        Game::setGhostsLevel(GHOST_TYPE::GOOD_GHOST_LEVEL);
        break;
    case GHOST_TYPE::NOVICE_GHOST_LEVEL:
        Game::setGhostsLevel(GHOST_TYPE::NOVICE_GHOST_LEVEL);
        break;
    default:break;
    }
}
void GameMenu::gameEnd(int lives_pac,bool atLeast1BoardFinish)
{
    if (Game::getGameMode() == Game::GAME_MODE::LOAD_SILENTLY)
    {
        gameOption = OPTION::EXIT;
        return;
    }
    if (!atLeast1BoardFinish)
        return;
       
    GameBoard::clearScreen();
    if (lives_pac == 0)
    {
        //if game is with colors, we change the gameover text to red and then return it to whitegrey
        if (Game::active_color)
            setTextColor(Color::RED);

        cout <<"  ######       ###     ##     ##  ########      #######   ##     ##  ########  ########   #### \n"
            << " ##    ##     ## ##    ###   ###  ##           ##     ##  ##     ##  ##        ##     ##  ####\n"
            << " ##          ##   ##   #### ####  ##           ##     ##  ##     ##  ##        ##     ##  ####\n"
            << " ##   ####  ##     ##  ## ### ##  ######       ##     ##  ##     ##  ######    ########    ## \n"
            << " ##    ##   #########  ##     ##  ##           ##     ##   ##   ##   ##        ##   ##        \n"
            << " ##    ##   ##     ##  ##     ##  ##           ##     ##    ## ##    ##        ##    ##   ####\n"
            << "  ######    ##     ##  ##     ##  ########      #######      ###     ########  ##     ##  ####   "<< endl;
       
    }
    else//you won the game
    {
        if (Game::active_color)
            setTextColor(Color::GREEN);

        cout <<"##    ##   #######   ##     ##     ##      ##  ####  ##    ##  #### \n"
             <<" ##  ##   ##     ##  ##     ##     ##  ##  ##   ##   ###   ##  ####  \n"
             <<"  ####    ##     ##  ##     ##     ##  ##  ##   ##   ####  ##  ####  \n"
             <<"   ##     ##     ##  ##     ##     ##  ##  ##   ##   ## ## ##   ##   \n"
             <<"   ##     ##     ##  ##     ##     ##  ##  ##   ##   ##  ####        \n"
             <<"   ##     ##     ##  ##     ##     ##  ##  ##   ##   ##   ###  ####  \n"
             <<"   ##      #######    #######       ###  ###   ####  ##    ##  ####    " << endl;

    }

    if (Game::active_color)
        setTextColor(Color::LIGHTGREY);
    


    if (Game::getGameMode() == Game::GAME_MODE::LOAD)
    {
        gameOption = OPTION::EXIT;
        return;
    }
    cout << "\npress any key to return game menu" << endl;
    while (!_kbhit()) {}//wait for user input
    char temp = _getch();//clean buffer

}

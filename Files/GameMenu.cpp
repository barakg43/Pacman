#include "GameMenu.h"
#include "io_utils.h"
#include "GameBoard.h"
#include "Game.h"






void GameMenu::Print(bool& runGame)
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
        case OPTION::HOW_TO_PLAY:
            howToPlay();
            break;
        case OPTION::EXIT:
            break;

        default:;
        }
        if (gameOption != OPTION::EXIT)
            gameOption = OPTION::NOT_INIT;//for reset game menu
    
}
int  GameMenu::getGameMenuOptionFromUser()
{
    char userChoice = NOT_INIT;
    cout << "#############################\n"
        << "#1  -Start The Game         #\n"
        << "#2  -Start with colors      #\n"
        << "#3  -Change game speed      #\n"
        << "#8  -How To Play            #\n"
        << "#9  -Exit                   #\n"
        << "#############################\n";

    userChoice = _getch();


    while ((userChoice > '9' || userChoice < '8') && (userChoice < '1' || userChoice>'3'))
    {
        gotoxy(5, 10);
        clog << "Not valid game menu option\nPlease enter number between 1,2,3,8 or 9" << endl;
        gotoxy(0, 0);
        userChoice = _getch();
    }




    if (userChoice == '1' || userChoice == '2')
    {
        GameBoard::clearScreen();
        if (Game::active_color)
            setTextColor(Color::YELLOW);
        cout << " __   _     __       _  _     _    _                " << endl;
        cout << "|__) /_\\   /    __  / \\/ \\   /_\\  | \\ |        " << endl;
        cout << "|   /   \\  \\__     /      \\ /   \\ |  \\|        " << endl << endl;
        if (Game::active_color)
            setTextColor(Color::LIGHTGREY);

        Sleep(500);
    }



    return userChoice - '0';
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
    cout << "#1 FAST SPEED" << endl
         << "#2 REGULAR SPEED" << endl
         << "#3 SLOW SPEED" << endl;
    char userChoice = OPTION::NOT_INIT;
    do
    {
        userChoice = _getch();
        gotoxy(5, 10);
        clog << "Not valid speed option\nPlease enter number between 1,2,3" << endl;
        gotoxy(0, 0);
    } while (userChoice < '1' || userChoice>'3');
    switch (userChoice)
    {
    case FAST:
        Game::setGameSpeed(Game::FAST_GAME_SPEED);
        break;
    case NORMAL:
        Game::setGameSpeed(Game::NORMAL_GAME_SPEED);
        break;
        break;
    case SLOW:
        Game::setGameSpeed(Game::SLOW_GAME_SPEED);
        break;
    default:;
    }

}

void GameMenu::gameEnd(int lives_pac)
{

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

    cout << "\npress any key to return game menu" << endl;
    while (!_kbhit()) {}//wait for user input
    char temp = _getch();//clean buffer

}



/*
void GameMenu::print()
{
    Game* temp;
    gameOption = NOT_INIT;

    while (gameOption == Game::NOT_INIT)
    {

        GameBoard::clearScreen();

        gameOption = getGameMenuOptionFromUser();
        switch (gameOption)
        {
        case 1:
           _moveCounter = 15;
           Game::gameLoop();
            break;
        case 2:
            Game::active_color = true;
            gameLoop();
            break;
        case 3:
            gameSpeedMenu();
            break;
        case 8:
            howToPlay();
            break;
        case EXIT:
            break;

        default:;
        }
        if (gameOption != EXIT)
            gameOption = NOT_INIT;//for reset game menu
    }
}
int  GameMenu::getGameMenuOptionFromUser()
{
    char userChoice = NOT_INIT;
    cout << "#############################\n"
        << "#1  -Start The Game         #\n"
        << "#2  -Start with colors      #\n"
        << "#3  -Change game speed      #\n"
        << "#8  -How To Play            #\n"
        << "#9  -Exit                   #\n"
        << "#############################\n";

    userChoice = _getch();


    while ((userChoice > '9' || userChoice < '8') && (userChoice < '1' || userChoice>'3'))
    {
        gotoxy(5, 10);
        clog << "Not valid game menu option\nPlease enter number between 1,2,3,8 or 9" << endl;
        gotoxy(0, 0);
        userChoice = _getch();
    }






    return userChoice - '0';
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
    cout << "#1 FAST SPEED" << endl
        << "#2 REGULAR SPEED" << endl
        << "#3 SLOW SPEED" << endl;
    char userChoice = Game::NOT_INIT;
    do
    {
        userChoice = _getch();
        gotoxy(5, 10);
        clog << "Not valid speed option\nPlease enter number between 1,2,3" << endl;
        gotoxy(0, 0);
    } while (userChoice < '1' || userChoice>'3');
    switch (userChoice)
    {
    case FAST:
        Game::setGameSpeed(Game::FAST_GAME_SPEED);
        break;
    case NORMAL:
        Game::setGameSpeed(Game::NORMAL_GAME_SPEED);
        break;
        break;
    case SLOW:
        Game::setGameSpeed(Game::SLOW_GAME_SPEED);
        break;
    default:;
    }

}*/
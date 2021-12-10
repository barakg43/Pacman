#include "GameMenu.h"
#include "io_utils.h"
#include "GameBoard.h"






void GameMenu::print()
{

    gameOption = NOT_INIT;

    while (gameOption == NOT_INIT)
    {

        GameBoard::clearScreen();

        gameOption = getGameMenuOptionFromUser();
        switch (gameOption)
        {
        case 1:
            gameLoop();
            break;
        case 2:
            active_color = true;
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



    if (active_color)
        setTextColor(Color::YELLOW);
    clear_screen();
    cout << " __   _     __       _  _     _    _                " << endl;
    cout << "|__) /_\\   /    __  / \\/ \\   /_\\  | \\ |        " << endl;
    cout << "|   /   \\  \\__     /      \\ /   \\ |  \\|        " << endl << endl;
    if (active_color)
        setTextColor(Color::LIGHTGREY);

    Sleep(500);



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
    clear_screen();
    cout << "#1 FAST SPEED" << endl
        << "#2 REGULAR SPEED" << endl
        << "#3 SLOW SPEED" << endl;
    char userChoice = NOT_INIT;
    do
    {
        userChoice = _getch();
        gotoxy(5, 10);
        clog << "Not valid speed option\nPlease enter number between 1,2,3" << endl;
        gotoxy(0, 0);
    } while (userChoice < '1' || userChoice>'3');
    switch (userChoice)
    {
    case '1':
        gameSpeed = FAST_GAME_SPEED;
        break;
    case '2':
        gameSpeed = NORMAL_GAME_SPEED;
        break;
    case '3':
        gameSpeed = SLOW_GAME_SPEED;


    }

}

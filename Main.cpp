//#include <iostream>
//#include <string.h>
//#include "Point.h"
//#include "Pacman.h"
//#include "Ghost.h"
//#include "GameBoard.h"
#include "Game.h"

int main(int argc, char** argv)
{



	Game game;

	game.getCommandLineArguments(argc, argv);
	game.start();
	

	return 0;
}


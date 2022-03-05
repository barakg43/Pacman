#include "ExceptionsManager.h"
#include <iostream>
#include "GameBoard.h"
ExceptionsManager* ExceptionsManager::insertExcp(const string& msg)
{
	excpMsg.push_back(msg);
	return this;
}

void ExceptionsManager::printAllMsg()
{
		GameBoard::clearScreen();
		for (auto itr : excpMsg)
		{
		
			std::cout <<"ERROR! " <<itr << std::endl;
			
		}
		excpMsg.clear();
		std::cout << std::endl;
	
	
}

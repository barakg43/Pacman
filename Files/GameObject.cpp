//#include "GameObject.h"
//#include "Game.h"
//#include"GameBoard.h"
//
//void GameObject::drawObject(GameObject& obj, Point& pos)
//{
//    int oldX = pos.getX(), oldY = pos.getY(), newX = obj.getPosition().getX(), newY = obj.getPosition().getY();
//    char oldPosChar = _board.getCurrBoardChar(oldX, oldY);
//    gotoxy(oldX, oldY);
//    if (active_color)
//        setTextColor(LIGHTGREY);
//    _putch(oldPosChar);
//    if (active_color)
//        setTextColor(LIGHTGREEN);
//    gotoxy(newX, newY);
//
//
//    _putch(ghost.getFigure());
//}
#pragma once

//UI based on chess tutorial: https://www.youtube.com/watch?v=_4EuZI8Q8cs
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Constants.h"

using namespace sf;

class UI
{
public:
	RenderWindow window;

	UI();
	void loadBoard(int** amazonsPos, std::string boardPath, std::string queensPath, std::string arrowPath, std::string winMsgPath);
	void display();

	Vector2i pickAmazon(); 
	Vector2i dropAmazon(); 
	Vector2i chooseArrowPlace();
	void setAmazonPosition(Vector2i mousePos);
	void placeArrow(Vector2i arrowPos);
	void changeAmazonPosition(Vector2i oldPos, Vector2i newPos);
	void displayWinner(int teamColor);
	void waitClose();
	void closeWindow();



private:

	Vector2i delta; // diffetence between the edge of a square and mouse place on a square (for dragging amazon by any place, not a corner)
	int n = -1; // amazon, being moved durind cuttent move. -1 -> no one (no move happening)

	int arrowCount = 0; // Amount of arrows on board

	Texture tBoard, tQueens, tArrow, tWinMsg;
	Sprite sBoard, sQueens[c::AMAZONS], sArrows[c::MAX_ARROWS], sWinMsg[2];

	void loadQueens(int** amazonsPos);
	void loadArrows();
	void loadWinMsg();

};

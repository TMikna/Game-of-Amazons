#include "UI.h"
#include <chrono>  //for sleep
#include <thread>  //for sleep

#include <algorithm>
#include <iostream>
#include <stdint.h>
#include <fstream>
#include <list>

//UI based on chess tutorial: https://www.youtube.com/watch?v=_4EuZI8Q8cs

UI::UI()
{
    window.create(VideoMode(cUI::BOARD_WIDTH, cUI::BOARD_HEIGHT), "The Game of the Amazons");
}

void UI::loadBoard(int** amazonsPos, std::string boardPath, std::string queensPath, std::string arrowPath, std::string winMsgPath)
{
	tBoard.loadFromFile(boardPath);
	sBoard.setTexture(tBoard, true);

	tQueens.loadFromFile(queensPath);
	loadQueens(amazonsPos);

	tArrow.loadFromFile(arrowPath);
	loadArrows();

	tWinMsg.loadFromFile(winMsgPath);
	loadWinMsg();

	display();
};

void UI::display()
{
	window.clear();
	window.draw(sBoard);
	for (int i = 0; i < c::AMAZONS; i++)
		window.draw(sQueens[i]);

	for (int i = 0; i < arrowCount; i++)
		window.draw(sArrows[i]);

	for (int i = 0; i < 2; i++)
		window.draw(sWinMsg[i]);
	
	window.display();
}

void UI::loadQueens(int** amazonsPos)
{
	for (int k = 0; k < c::AMAZONS; k++)
		{
			sQueens[k].setTexture(tQueens);
			int type = amazonsPos[k][0];
			int i = amazonsPos[k][1];
			int j = amazonsPos[k][2];
			sQueens[k].setTextureRect(IntRect(0, cUI::SQUARE_SIZE * (type % 2), cUI::SQUARE_SIZE, cUI::SQUARE_SIZE));
			sQueens[k].setPosition(cUI::SQUARE_SIZE * j, cUI::SQUARE_SIZE * i);
		}
	//for (int i = 0; i < position.length(); i += 5)
	//	move(position.substr(i, 4));
}

void UI::loadArrows()
{
	for (int i = 0; i < c::MAX_ARROWS; i++)
	{
		sArrows[i].setTexture(tArrow);
		sArrows[i].setPosition(-100, -100);
	}
}

void UI::loadWinMsg()
{
	sWinMsg[0].setTexture(tWinMsg);
	sWinMsg[0].setTextureRect(IntRect(0, cUI::WIN_MSG_HEIGHT * 0, cUI::WIN_MSG_WIDTH, cUI::WIN_MSG_HEIGHT));
	sWinMsg[0].setPosition(-200,-200);

	sWinMsg[1].setTexture(tWinMsg);
	sWinMsg[1].setTextureRect(IntRect(0, cUI::WIN_MSG_HEIGHT * 1, cUI::WIN_MSG_WIDTH, cUI::WIN_MSG_HEIGHT));
	sWinMsg[1].setPosition(-200, -200);
}

void UI::displayWinner(int teamColor)
{
	int x = cUI::BOARD_WIDTH / 2 - cUI::WIN_MSG_WIDTH / 2;
	int y = cUI::BOARD_HEIGHT / 2 - cUI::WIN_MSG_HEIGHT / 2;
	sWinMsg[teamColor-1].setPosition(x, y);
	display();
}

void UI::waitClose()
{
	Event e;
	do
	{
		window.waitEvent(e);
	} while (e.type != Event::Closed);

	if (e.type == Event::Closed)
	window.close();
}

void UI::closeWindow()
{
	window.close();
}




//TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// moving amazons


Position UI::pickAmazon()
{
	Event e;
	while(window.isOpen())  // at least better than while(true)
	{	
		window.waitEvent(e);

		if (e.type == Event::Closed)
			window.close();

		Vector2i mousePos = Mouse::getPosition(window);

		if (e.type == Event::MouseButtonPressed)
			if (e.key.code == Mouse::Left)
				for (int i = 0; i < c::AMAZONS; i++)
					if (sQueens[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
					{
						Vector2f winPos = sQueens[i].getPosition();  // amazon position on window, in pixels
						
						n = i;   //set current amazon
						int dx = mousePos.x - winPos.x;
						int dy = mousePos.y - winPos.y;
						delta = Position(dx, dy);

						// x and y changes places because windiw is as a coordinate plane and Board holds positions in a matrix, hence y becoles row and x - colum
						Position pos = Position(winPos.y / cUI::SQUARE_SIZE, winPos.x / cUI::SQUARE_SIZE);
						return pos;
					}
	 }
}

Position UI::dropAmazon()
{
	Event e;
	while (window.isOpen())  // at least better than while(true)
	{
		Vector2i mousePos = Mouse::getPosition(window);
		while (!window.pollEvent(e))  // exting when event occurs
		{
			// Allow dragging - an amazon follows the mouse
			mousePos = Mouse::getPosition(window);
			sQueens[n].setPosition(mousePos.x - delta.x, mousePos.y - delta.y);
			display();
			// Little sleep to reduce CPU load
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}

		if (e.type == Event::Closed)
			window.close();

		if (e.type == Event::MouseButtonReleased)
			if (e.key.code == Mouse::Left)
			{
				Position pos = Position(mousePos.y / cUI::SQUARE_SIZE, mousePos.x / cUI::SQUARE_SIZE);
				return pos;
			}
	}
}

void UI::setAmazonPosition(Position pos)
{
	sQueens[n].setPosition(pos.y * cUI::SQUARE_SIZE, pos.x * cUI::SQUARE_SIZE);
	display();
}

void UI::changeAmazonPosition(Position oldPos, Position newPos)
{
	// find position 
	for (int i = 0; i < c::AMAZONS; i++)
		if (sQueens[i].getGlobalBounds().contains(oldPos.y * cUI::SQUARE_SIZE, oldPos.x * cUI::SQUARE_SIZE))
		{
			n = i; // set currently used amazon
			setAmazonPosition(newPos);
			return;
		}
}



//TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
// placing arrows

Position UI::chooseArrowPlace()
{
	Event e;
	while (window.isOpen())  // at least better than while(true)
	{
		Vector2i mousePos = Mouse::getPosition(window);

		window.waitEvent(e);

		if (e.type == Event::Closed)
			window.close();

		if (e.type == Event::MouseButtonPressed)
			if (e.key.code == Mouse::Left)
				return Position(mousePos.y / cUI::SQUARE_SIZE, mousePos.x / cUI::SQUARE_SIZE);
	}
}

void UI::placeArrow(Position arrowPos)
{
	sArrows[arrowCount].setPosition(arrowPos.y * cUI::SQUARE_SIZE, arrowPos.x * cUI::SQUARE_SIZE);
	arrowCount++;

	n = -1; //move finished, no amazon is currenly moved

	display();
}



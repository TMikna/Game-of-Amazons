#pragma once
#include "Player.h"
#include "UI.h"
class Person :
    public Player
{
public:
	Person(Board *board, UI *ui, int teamColor)
	{
		this->board = board;
		this->ui = ui;
		this->teamColor = teamColor;
	}
	//Virtual function
	virtual void moveAmazon();
	virtual void shootArrow();

private:
	int teamColor = -1; // whites or blacks, -1 = neither
	UI *ui;
	Board *board;
	Vector2i oldPos, newPos, arrowPos;
};


#pragma once
#include "Player.h"
#include "UI.h"
class Person :
    public Player
{
public:
	Person(Board *board, UI *ui, int teamColor):Player(teamColor)
	{
		this->board = board;
		this->ui = ui;

	}
	//Virtual function
	virtual void moveAmazon();
	virtual void shootArrow();
	virtual bool hasPossibleMove();

private:
	UI *ui;
	Board *board;
	Position oldPos, newPos, arrowPos;
};


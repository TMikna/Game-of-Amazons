#pragma once
#include "Player.h"
#include "UI.h"

class RandomAI :
	public Player
{
public:
	RandomAI(Board* board, UI* ui, int teamColor):Player(teamColor)
	{
		this->board = board;
		this->ui = ui;
	}
	//Virtual function
	virtual void moveAmazon();
	virtual void shootArrow();
	virtual bool hasPossibleMove();


private:
	UI* ui;
	Board* board;
	Position oldPos, newPos, arrowPos;
	AmazonMove move; //holds oldPos and newPos
	// int** amazons; //amazons, controlled by AI;

	inline int chooseMove(int max);
};
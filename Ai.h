#pragma once
#include "Player.h"
#include "UI.h"

class Ai :
	public Player
{
public:
	Ai(Board* board, UI* ui, int teamColor)
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
	UI* ui;
	Board* board;
	Vector2i oldPos, newPos, arrowPos;
	AmazonMove move; //holds oldPos and newPos
	// int** amazons; //amazons, controlled by AI;

	inline int chooseMove(int max);

};
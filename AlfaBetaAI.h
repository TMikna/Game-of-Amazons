#pragma once
#include "Player.h"
#include "UI.h"


class AlfaBetaAI :
    public Player
{

public:
	AlfaBetaAI(Board* board, UI* ui, int teamColor):Player(teamColor)
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
	Vector2i oldPos, newPos, arrowPos;
	AmazonMove move; //holds oldPos and newPos
	// int** amazons; //amazons, controlled by AI;

	inline double AlfaBeta(Board* searchBoard, int depth, bool maximizingPlayer);


	inline int chooseMove(int max);
	inline double Evaluate(Board* board, int nextMovingTeamColor);

};

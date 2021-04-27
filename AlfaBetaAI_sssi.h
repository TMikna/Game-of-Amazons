#pragma once
#include "Player.h"
#include "UI.h"
class AlfaBetaAI_sssi :
    public Player
{

public:
	AlfaBetaAI_sssi(Board* board, UI* ui, int teamColor) :Player(teamColor)
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

	inline float AlfaBeta(Board* searchBoard, int depth, float alpha, float beta, bool maximizingPlayer);
	inline float AlfaBetaArrow(Board* searchBoard, int depth, float alpha, float beta, bool maximizingPlayer, AmazonMove bestMove);
	inline float Evaluate(Board* board, int nextMovingTeamColor);

};


#pragma once
#include "Player.h"
#include "UI.h"
#include "Board.h"

/// <summary>
/// Alfa-Bera prining AI with full search of moves (compared to another when arrows are searched only for the best amazon)
/// </summary>
class AlfaBetaAI_fs :
    public Player
{
	public:
		AlfaBetaAI_fs(Board* board, UI* ui, int teamColor) :Player(teamColor)
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
		inline float Evaluate(Board* board, int nextMovingTeamColor);

};


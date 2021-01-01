#include "RandomAI.h"
#include <iostream>

void RandomAI::moveAmazon()
{
	// all possible moves with all player amazons
	auto moves = board->findAllMoves(teamColor);

	// select random move from possible ones
	int moveCount = moves.size();
	AmazonMove move = moves[chooseMove(moveCount)];

	oldPos = move.from;
	newPos = move.to;

	ui->changeAmazonPosition(oldPos, newPos);
	board->moveAmazon(oldPos, newPos);
}

void RandomAI::shootArrow()
{
	auto mov = board->findAllMovesFrom(newPos);
	std::vector<AmazonMove> moves = mov;
	int moveCount = moves.size();
	AmazonMove move = moves[chooseMove(moveCount)];
	arrowPos = move.to;

	board->placeArrow(arrowPos);
	ui->placeArrow(arrowPos);
}

inline int RandomAI::chooseMove(int max)
{
	/* initialize random seed: */
	srand(time(NULL));

	/* generate secret number between 0 and max: */
	return rand() % max;
}

bool RandomAI::hasPossibleMove()
{
	return board->hasMove(teamColor);
}
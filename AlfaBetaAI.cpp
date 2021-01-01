#include "AlfaBetaAI.h"

void AlfaBetaAI::moveAmazon()
{
	int maxDepth = c::MAX_SEARCH_DEPTH;
	// use copy so searching process do not disturb the original game state
	Board boardCopy(board->getBoardState());
	AmazonMove nextMove;

#pragma region Modilied 1st layer of alfa-beta search

	float maxEva = -std::numeric_limits<float>::max(); // -infinity (closest we can get). Less than -2*10^9
	//if (!board->hasMove(teamColor)) //Lost, should never get here
	
	auto possibleMoves = boardCopy.findAllMoves(teamColor);
	for (auto &move : possibleMoves) // access by reference to avoid copying
	{
		boardCopy.moveAmazon(move);
		float evaluation = AlfaBeta(&boardCopy, maxDepth -1, false);
		if (evaluation > maxEva)
		{
			maxEva = evaluation;
			nextMove = move;
		}
		boardCopy.moveAmazon(move.to, move.from);    //undo move before exiting
	}
#pragma endregion

	//AmazonMove move = moves[chooseMove(moveCount)];
//	AmazonMove move = AlfaBeta();

	oldPos = nextMove.from;
	newPos = nextMove.to;

	ui->changeAmazonPosition(oldPos, newPos);
	board->moveAmazon(oldPos, newPos);
}

//TODO next: add arrows
//Is it better to find best move and then best arrow sott for it
//Or best move + arrow (find all moves and all possible arrow possitions and find the best? This sounds better and easier to implement but a lot move performance expensive
inline float AlfaBetaAI::AlfaBeta(Board *searchBoard, int depth, bool maximizingPlayer)
{
	// moved into each player's section since my evaluation needs to know who's moving next
	//if (depth == 0)
	//{
	//	return Evaluate(searchBoard)
	//}
		
	if (maximizingPlayer)      // for Maximizer Player  
	{
		if (depth == 0 || !board->hasMove(teamColor)) // Reached dec]sired depth or end of the game
			return Evaluate(searchBoard, teamColor);

		float maxEva = -std::numeric_limits<float>::max(); // -infinity (closest we can get). Less than -2*10^9
		auto possibleMoves = searchBoard->findAllMoves(teamColor);
		for (auto &move : possibleMoves) // access by reference to avoid copying
		{
			searchBoard->moveAmazon(move);
			float evaluation = AlfaBeta(searchBoard, depth - 1, false);
			maxEva = maxEva >= evaluation ? maxEva : evaluation;        //gives Maximum of the values  
			searchBoard->moveAmazon(move.to, move.from);	               //undo move before exitingž
		}
		return maxEva;

	}
	else
	{	// for Minimizer player  
		if (depth == 0 || !board->hasMove(oppositeTeamColor)) // Reached dec]sired depth or end of the game
			return Evaluate(searchBoard, oppositeTeamColor);

		float minEva = std::numeric_limits<float>::max(); // +infinity (closest we can get). More than 2*10^9
		auto possibleMoves = searchBoard->findAllMoves(oppositeTeamColor);
		for (auto &move : possibleMoves) // access by reference to avoid copying
		{
			searchBoard->moveAmazon(move);
			float evaluation = AlfaBeta(searchBoard, depth - 1, true);
			minEva = minEva <= evaluation ? minEva : evaluation;
			searchBoard->moveAmazon(move.to, move.from);	               //undo move before exiting	
		}
		return minEva;
	}
}


// Editing Evaluation formula no possible move case in AlfaBetaAI should be reviewed
inline float AlfaBetaAI::Evaluate(Board* board, int nextMovingTeamColor)
{
	float bias = 0.5;
	if (nextMovingTeamColor == teamColor)
		bias *= -1;
	int movCount = board->countAllMoves(teamColor);
	int enemyMovCount = board->countAllMoves(oppositeTeamColor);

	// evaluation = moves difference divided by moves sum
	// evaluaion range [-1;1] 0 is neutral, is positive - player is in better possition. The closer to 1 the better. Same the more negative the worse position it is
	float evaluation = (float(movCount - enemyMovCount) + bias) / (float(movCount + enemyMovCount) + std::abs(bias));
	// bias for: it can happen that there's 0 free spaces. Then the one moving next loses
	// It might also help getting close to such position
	return evaluation;
}

bool AlfaBetaAI::hasPossibleMove()
{
	return board->hasMove(teamColor);
}

#pragma region TODO_Random_move_part
void AlfaBetaAI::shootArrow()
{
	auto mov = board->findAllMovesFrom(newPos);
	std::vector<AmazonMove> moves = *mov;
	int moveCount = moves.size();
	AmazonMove move = moves[chooseMove(moveCount)];
	arrowPos = move.to;

	board->placeArrow(arrowPos);
	ui->placeArrow(arrowPos);
}

inline int AlfaBetaAI::chooseMove(int max)
{
	/* initialize random seed: */
	srand(time(NULL));

	/* generate secret number between 0 and max: */
	return rand() % max;
}
#pragma endregion


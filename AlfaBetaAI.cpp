#include "AlfaBetaAI.h"

void AlfaBetaAI::moveAmazon()
{
	int maxDepth = c::MAX_SEARCH_DEPTH;
	// use copy so searching process do not disturb the original game state
	Board boardCopy(board->getBoardState());
	AmazonMove nextMove;

#pragma region Modilied 1st half of 1st layer of alfa-beta search
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


void AlfaBetaAI::shootArrow()
{
	int maxDepth = c::MAX_SEARCH_DEPTH;
	// use copy so searching process do not disturb the original game state
	Board boardCopy(board->getBoardState());
	AmazonMove arrowShoot;

#pragma region Modilied 1st half of 1st layer of alfa-beta search
	float maxEvaArrow = -std::numeric_limits<float>::max();             // -infinity (closest we can get)
	auto possibleArrows = boardCopy.findAllMovesFrom(newPos);
	for (auto& move : possibleArrows)                                    // access by reference to avoid copying
	{
		boardCopy.placeArrow(move.to);
		float evaluation = AlfaBeta(&boardCopy, maxDepth - 1, false);
		if (evaluation > maxEvaArrow)
		{
			maxEvaArrow = evaluation;
			arrowShoot = move;
		}		
		boardCopy.undoArrow(move.to);							   //undo move before exitingž
	}
#pragma endregion
	arrowPos = arrowShoot.to;

	board->placeArrow(arrowPos);
	ui->placeArrow(arrowPos);
}


//TODO next: add arrows
//Is it better to find best move and then best arrow sott for it
//Or best move + arrow (find all moves and all possible arrow possitions and find the best? This sounds better and easier to implement but a lot move performance expensive
inline float AlfaBetaAI::AlfaBeta(Board *searchBoard, int depth, bool maximizingPlayer)
{
	// moved into each player's section since my evaluation needs to know who's moving next
	//if (depth == 0){ return Evaluate(searchBoard) }
		
	if (maximizingPlayer)      // for Maximizer Player  
	{
		if (depth == 0 || !board->hasMove(teamColor)) // Reached dec]sired depth or end of the game
			return Evaluate(searchBoard, teamColor);

		AmazonMove bestMove;
		float maxEva = -std::numeric_limits<float>::max(); // -infinity (closest we can get). Less than -2*10^9
		auto possibleMoves = searchBoard->findAllMoves(teamColor);

		for (auto &move : possibleMoves) // access by reference to avoid copying
		{
			searchBoard->moveAmazon(move);
			float evaluation = AlfaBeta(searchBoard, depth - 1, false);
			if (evaluation > maxEva)
			{
				maxEva = evaluation;
				bestMove = move;
			}			
			searchBoard->moveAmazon(move.to, move.from);	                //undo move before exitingž
		}

		searchBoard->moveAmazon(bestMove.from, bestMove.to);				//Do the best move, and then find best arrow pos from new position
		float maxEvaArrow = -std::numeric_limits<float>::max();             // -infinity (closest we can get)
		auto possibleArrows = searchBoard->findAllMovesFrom(bestMove.to);
		for (auto& move : possibleArrows)                                    // access by reference to avoid copying
		{
			searchBoard->placeArrow(move.to);
			float evaluation = AlfaBeta(searchBoard, depth - 1, false);
			maxEvaArrow = maxEvaArrow >= evaluation ? maxEvaArrow : evaluation;	  //gives Maximum of the values  
			searchBoard->undoArrow(move.to);							   //undo move before exitingž
		}
		searchBoard->moveAmazon(bestMove.to, bestMove.from);					  //undo the move
		return maxEvaArrow;												   //Returning arrow evaluation because it is board state evaluation after whole move
	}

	else
	{	// for Minimizer player  
		if (depth == 0 || !board->hasMove(oppositeTeamColor)) // Reached dec]sired depth or end of the game
			return Evaluate(searchBoard, oppositeTeamColor);

		AmazonMove worstMove;
		float minEva = std::numeric_limits<float>::max(); // +infinity (closest we can get)
		auto possibleMoves = searchBoard->findAllMoves(oppositeTeamColor);

		for (auto &move : possibleMoves) // access by reference to avoid copying
		{
			searchBoard->moveAmazon(move);
			float evaluation = AlfaBeta(searchBoard, depth - 1, true);
			if (evaluation < minEva)
			{
				minEva = evaluation;
				worstMove = move;
			}
			searchBoard->moveAmazon(move.to, move.from);	                //undo move before exiting	
		}																    
																		    
		searchBoard->moveAmazon(worstMove.from, worstMove.to);			    //Do the worst move, and then find worst arrow pos from new position
		float minEvaArrow = std::numeric_limits<float>::max();			    // +infinity (closest we can get with float)
		auto possibleArrows = searchBoard->findAllMovesFrom(worstMove.to);  

		for (auto& move : possibleArrows)								    // access by reference to avoid copying
		{
			searchBoard->placeArrow(move.to);								//place arrow
			float evaluation = AlfaBeta(searchBoard, depth - 1, true);
			minEvaArrow = minEvaArrow <= evaluation ? minEvaArrow : evaluation;
			searchBoard->undoArrow(move.to);	                            //undo arrow before exiting	
		}																 
		searchBoard->moveAmazon(worstMove.to, worstMove.from);			    //Undo the best move before leaving
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

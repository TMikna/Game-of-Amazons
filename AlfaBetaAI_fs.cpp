#include "AlfaBetaAI_fs.h"

void AlfaBetaAI_fs::moveAmazon()
{
	int maxDepth = c::MAX_SEARCH_DEPTH;
	// use copy so searching process do not disturb the original game state
	Board boardCopy(board->getBoardState());

#pragma region Modilied 1st half of 1st layer of alfa-beta search
	
	float maxEva = -std::numeric_limits<float>::max();			// -infinity (closest we can get)
	//if (!board->hasMove(teamColor)) //Lost, should never get here
	float alpha = -std::numeric_limits<float>::max();			// -infinity (closest we can get). Less than -2*10^9
	float beta = std::numeric_limits<float>::max();				// -infinity (closest we can get). Less than -2*10^9

	auto possibleMoves = boardCopy.findAllMoves(teamColor);
	for (auto& move : possibleMoves) // access by reference to avoid copying
	{
		boardCopy.moveAmazon(move.from, move.to);						// do a move
		auto possibleArrows = boardCopy.findAllMovesFrom(move.to);   // check all possible arrows from there
		for (auto& arrow : possibleArrows)
		{
			boardCopy.placeArrow(arrow.to);

			float evaluation = AlfaBeta(&boardCopy, maxDepth - 1, alpha, beta, false);
			if (evaluation >= maxEva)
			{
				maxEva = evaluation;

				// Save current best move
				oldPos = move.from;
				newPos = move.to;
				arrowPos = arrow.to;
			}

			boardCopy.undoArrow(arrow.to);					   //undo arrow before trying another position

			// alfa-beta pruning
			alpha = alpha >= maxEva ? alpha : maxEva;
			if (alpha >= beta)
				break;
		}
		boardCopy.moveAmazon(move.to, move.from);	                //undo move before trying another position
		if (alpha >= beta)
			break;
	}
#pragma endregion

//	oldPos = nextMove.from;
//	newPos = nextMove.to;

	ui->changeAmazonPosition(oldPos, newPos);
	board->moveAmazon(oldPos, newPos);
}


void AlfaBetaAI_fs::shootArrow()
{
	// move amazon finds best move and arrow placement combination

	board->placeArrow(arrowPos);
	ui->placeArrow(arrowPos);
}



//Checking all possible move are arrow shoot combinations (except those who are cut by albe-beta pruning)
inline float AlfaBetaAI_fs::AlfaBeta(Board* searchBoard, int depth, float alpha, float beta, bool maximizingPlayer)
{
	// moved into each player's section since my evaluation needs to know who's moving next
	//if (depth == 0){ return Evaluate(searchBoard) }

	if (maximizingPlayer)      // for Maximizer Player  
	{
		if (depth == 0 || !searchBoard->hasMove(teamColor)) // Reached decsired depth or end of the game
			return Evaluate(searchBoard, teamColor);

		float maxEva = -std::numeric_limits<float>::max(); // -infinity (closest we can get)
		auto possibleMoves = searchBoard->findAllMoves(teamColor);
		std::vector <AmazonMove> possibleArrows;
		for (auto& move : possibleMoves) // access by reference to avoid copying
		{
			searchBoard->moveAmazon(move.from, move.to);					// do a move
			possibleArrows = searchBoard->findAllMovesFrom(move.to);   // check all possible arrows from there

			for (auto& arrow : possibleArrows)
			{
				searchBoard->placeArrow(arrow.to);

				float evaluation = AlfaBeta(searchBoard, depth - 1, alpha, beta, false);
				maxEva = std::max(maxEva, evaluation);	  //gives Maximum of the values  

				searchBoard->undoArrow(arrow.to);					   //undo arrow before trying another position
					
				// alfa-beta pruning
				alpha = std::max(alpha, maxEva);
				if (alpha >= beta)
					break;
			}
			searchBoard->moveAmazon(move.to, move.from);	                //undo move before trying another position

			if (alpha >= beta)
				break;
		}
		return maxEva;												   //Returning arrow evaluation because it is board state evaluation after whole move
	}

	else
	{	// for Minimizer player  
		if (depth == 0 || !searchBoard->hasMove(oppositeTeamColor)) // Reached desired depth or end of the game
			return Evaluate(searchBoard, oppositeTeamColor);

		float minEva = std::numeric_limits<float>::max(); // +infinity (closest we can get)
		auto possibleMoves = searchBoard->findAllMoves(oppositeTeamColor);
		std::vector <AmazonMove> possibleArrows;
		for (auto& move : possibleMoves) // access by reference to avoid copying
		{
			searchBoard->moveAmazon(move.from, move.to);					// do a move
			possibleArrows = searchBoard->findAllMovesFrom(move.to);   // check all possible arrows from there

			for (auto& arrow : possibleArrows)
			{
				searchBoard->placeArrow(arrow.to);

				float evaluation = AlfaBeta(searchBoard, depth - 1, alpha, beta, true);
				minEva = std::min(minEva, evaluation);
				searchBoard->undoArrow(arrow.to);					   //undo arrow before trying another position

				// alfa-beta pruning
				beta = std::min(beta, minEva);
				if (alpha >= beta)
					break;
			}
			searchBoard->moveAmazon(move.to, move.from);	                //undo move before trying another position
			if (alpha >= beta)
				break;
		}
		return minEva;
	}
}

// Editing Evaluation formula no possible move case in AlfaBetaAI_ss should be reviewed
inline float AlfaBetaAI_fs::Evaluate(Board* board, int nextMovingTeamColor)
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

bool AlfaBetaAI_fs::hasPossibleMove()
{
	return board->hasMove(teamColor);
}

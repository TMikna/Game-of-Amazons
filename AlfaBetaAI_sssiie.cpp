#include "AlfaBetaAI_sssiie.h"

void AlfaBetaAI_sssiie::moveAmazon()
{
	int maxDepth = c::MAX_SEARCH_DEPTH;
	// use copy so searching process do not disturb the original game state
	Board boardCopy(board->getBoardState());
	AmazonMove nextMove;

#pragma region Modilied 1st half of 1st layer of alfa-beta search
	float maxEva = -std::numeric_limits<float>::max();		// -infinity (closest we can get)
	//if (!board->hasMove(teamColor))						//Lost, should never get here
	float alpha = -std::numeric_limits<float>::max();		// -infinity (closest we can get) 
	float beta = std::numeric_limits<float>::max();			// +infinity (closest we can get)

	auto possibleMoves = boardCopy.findAllMoves(teamColor);
	for (auto& move : possibleMoves)						// access by reference to avoid copying
	{
		boardCopy.moveAmazon(move.from, move.to);
		float evaluation = AlfaBetaArrow(&boardCopy, maxDepth, alpha, beta, true, move);
		if (evaluation >= maxEva)
		{
			maxEva = evaluation;
			nextMove = move;
		}
		boardCopy.moveAmazon(move.to, move.from);			//undo move before exiting
		// alfa-beta pruning
		alpha = std::max(alpha, maxEva);
		if (alpha >= beta)
			break;
	}
#pragma endregion

	//AmazonMove move = moves[chooseMove(moveCount)];
	//AmazonMove move = AlfaBeta();

	oldPos = nextMove.from;
	newPos = nextMove.to;

	ui->changeAmazonPosition(oldPos, newPos);
	board->moveAmazon(oldPos, newPos);
}

void AlfaBetaAI_sssiie::shootArrow()
{
	int maxDepth = c::MAX_SEARCH_DEPTH;
	// use copy so searching process do not disturb the original game state
	Board boardCopy(board->getBoardState());
	AmazonMove arrowShoot;

#pragma region Modilied 2nd half of 1st layer of alfa-beta search
	float maxEvaArrow = -std::numeric_limits<float>::max();              // -infinity (closest we can get)
	float alpha = -std::numeric_limits<float>::max();					 // -infinity (closest we can get)
	float beta = std::numeric_limits<float>::max();						 // +infinity (closest we can get)
	auto possibleArrows = boardCopy.findAllMovesFrom(newPos);
	for (auto& move : possibleArrows)                                    // access by reference to avoid copying
	{
		boardCopy.placeArrow(move.to);
		float evaluation = AlfaBeta(&boardCopy, maxDepth - 1, alpha, beta, false);
		if (evaluation >= maxEvaArrow)
		{
			maxEvaArrow = evaluation;
			arrowShoot = move;
		}
		boardCopy.undoArrow(move.to);									 //undo move before exiting

		// alfa-beta pruning
		alpha = std::max(alpha, maxEvaArrow);
		if (alpha >= beta)
			break;
	}
#pragma endregion
	arrowPos = arrowShoot.to;

	board->placeArrow(arrowPos);
	ui->placeArrow(arrowPos);
}


// Is it better to find best move and then best arrow shot for it - CURRENT
// AlfaBetaArrow() is second half of it
inline float AlfaBetaAI_sssiie::AlfaBeta(Board* searchBoard, int depth, float alpha, float beta, bool maximizingPlayer)
{
	// moved into each player's section since my evaluation needs to know who's moving next
	//if (depth == 0){ return Evaluate(searchBoard) }

	if (maximizingPlayer)      // for Maximizer Player  
	{
		if (depth == 0 || !searchBoard->hasMove(teamColor))					// Reached decsired depth or end of the game
			return Evaluate(searchBoard, teamColor);
		// it is not deeded in arriw part, because it gets into arroiw parf from amazon part and here depth is not reduced, also game cannot end

		//AmazonMove bestMove;
		float maxEva = -std::numeric_limits<float>::max();					// -infinity (closest we can get)
		auto possibleMoves = searchBoard->findAllMoves(teamColor);

		for (auto& move : possibleMoves)									// access by reference to avoid copying
		{
			searchBoard->moveAmazon(move.from, move.to);
			float evaluation = AlfaBetaArrow(searchBoard, depth, alpha, beta, true, move);
			if (evaluation > maxEva)
			{
				maxEva = evaluation;
				//bestMove = move;
			}
			searchBoard->moveAmazon(move.to, move.from);					 //undo move before exiting

			// alfa-beta pruning
			alpha = std::max(alpha, maxEva);
			if (alpha >= beta)
				break;

			return maxEva;
		}
	}

	else
	{	// for Minimizer player  
		if (depth == 0 || !searchBoard->hasMove(oppositeTeamColor))				// Reached decsired depth or end of the game
			return Evaluate(searchBoard, oppositeTeamColor);
		// it is not deeded in arrow part, because it gets into arroiw parf from amazon part and here depth is not reduced, also game cannot end


	//AmazonMove worstMove;
		float minEva = std::numeric_limits<float>::max();						 // +infinity (closest we can get)
		auto possibleMoves = searchBoard->findAllMoves(oppositeTeamColor);

		for (auto& move : possibleMoves)										 // access by reference to avoid copying
		{
			searchBoard->moveAmazon(move.from, move.to);
			float evaluation = AlfaBetaArrow(searchBoard, depth, alpha, beta, false, move);
			if (evaluation < minEva)
			{
				minEva = evaluation;
				//worstMove = move;
			}
			searchBoard->moveAmazon(move.to, move.from);						 //undo move before exiting	

			// alfa-beta pruning
			beta = std::min(beta, minEva);
			if (alpha >= beta)
				break;

			return minEva;
		}
	}
}


inline float AlfaBetaAI_sssiie::AlfaBetaArrow(Board* searchBoard, int depth, float alpha, float beta, bool maximizingPlayer, AmazonMove move)
{
	// moved into each player's section since my evaluation needs to know who's moving next
	//if (depth == 0){ return Evaluate(searchBoard) }

	if (maximizingPlayer)      // for Maximizer Player  
	{
		float maxEvaArrow = -std::numeric_limits<float>::max();						// -infinity (closest we can get)
		auto possibleArrows = searchBoard->findAllMovesFrom(move.to);
		for (auto& move : possibleArrows)											// access by reference to avoid copying
		{
			searchBoard->placeArrow(move.to);
			float evaluation = AlfaBeta(searchBoard, depth - 1, alpha, beta, false);
			maxEvaArrow = std::max(maxEvaArrow, evaluation);						//gives Maximum of the values  
			searchBoard->undoArrow(move.to);										//undo move before exitingž

			// alfa-beta pruning
			alpha = std::max(alpha, maxEvaArrow);
			if (alpha >= beta)
				break;
		}
		return maxEvaArrow;
		//Returning arrow evaluation because it is board state evaluation after whole move
	}

	else
	{	// for Minimizer player  

		float minEvaArrow = std::numeric_limits<float>::max();			    // +infinity (closest we can get with float)
		auto possibleArrows = searchBoard->findAllMovesFrom(move.to);

		for (auto& move : possibleArrows)								    // access by reference to avoid copying
		{
			searchBoard->placeArrow(move.to);								//place arrow
			float evaluation = AlfaBeta(searchBoard, depth - 1, alpha, beta, true);
			minEvaArrow = std::min(minEvaArrow, evaluation);
			searchBoard->undoArrow(move.to);	                            //undo arrow before exiting	

			// alfa-beta pruning
			beta = std::min(beta, minEvaArrow);
			if (alpha >= beta)
				break;
		}
		return minEvaArrow;
	}
}




// Editing Evaluation formula no possible move case in AlfaBetaAI_ss should be reviewed
inline float AlfaBetaAI_sssiie::Evaluate(Board* board, int nextMovingTeamColor)
{

	float cof1 = 0.3;
	float cof2 = 1 - cof1;

	float bias = 0.5;
	if (nextMovingTeamColor == teamColor)
		bias *= -1;
	int movCount = board->countAllMoves(teamColor);
	int enemyMovCount = board->countAllMoves(oppositeTeamColor);

	int movDirections = board->allPossibleDirections(teamColor);
	int enemyMovDirections = board->allPossibleDirections(oppositeTeamColor);

	// evaluation = moves difference divided by moves sum
	// evaluaion range [-1;1] 0 is neutral, is positive - player is in better possition. The closer to 1 the better. Same the more negative the worse position it is
	float mowEvaluation = (float(movCount - enemyMovCount) + bias) / (float(movCount + enemyMovCount) + std::abs(bias));
	// bias for: it can happen that there's 0 free spaces. Then the one moving next loses
	// It might also help getting close to such position

	float dirEvaluation = (float(movDirections - enemyMovDirections) + bias) / (float(movDirections + enemyMovDirections) + std::abs(bias));

	float evaluation = cof1*mowEvaluation + cof2*dirEvaluation;

	return evaluation;
}

bool AlfaBetaAI_sssiie::hasPossibleMove()
{
	return board->hasMove(teamColor);
}

#include "Board.h"
#include <iostream>
#include <deque>

void Board::printBoard()
{
	std::cout << std::endl;
	for (int i = 0; i < c::BOARD_SIZE; i++)
	{
		for (int j = 0; j < c::BOARD_SIZE; j++)
		{
			std::cout << board[i][j] << " ";
		}
		std::cout << std::endl;
	}
	
}

//std::vector<AmazonMove> Board::findAllMoves(int teamColor)
//{
//	std::vector<AmazonMove> moves;
//
//	for (int i = 0; i < c::BOARD_SIZE; i++)
//		for (int j = 0; j < c::BOARD_SIZE; j++)
//			if (board[i][j] == teamColor)
//			{
//				findAllMovesFrom(Position(i, j), &moves);
//			}
//
//	return moves;
//}

std::vector<AmazonMove> Board::findAllMoves(int teamColor)
{
	std::vector<AmazonMove> moves;
	moves.reserve(14);

	if (teamColor == WHITES)
		for(int i = 0; i< wAmazonsPositions.size(); i++)
			findAllMovesFrom(wAmazonsPositions[i], &moves);
	else if (teamColor == BLACKS)
		for (int i = 0; i < bAmazonsPositions.size(); i++)
			findAllMovesFrom(bAmazonsPositions[i], &moves);


	//for (int i = 0; i < c::BOARD_SIZE; i++)
	//	for (int j = 0; j < c::BOARD_SIZE; j++)
	//		if (board[i][j] == teamColor)
	//		{
	//			findAllMovesFrom(Position(i, j), &moves);
	//		}
	return moves;
}

// find all possible moves from a position
inline void Board::findAllMovesFrom(Position pos, std::vector<AmazonMove>* moves)
{
	int k;
	int l;

	// go down;
	k = pos.x;
	l = pos.y;
	while (++k < c::BOARD_SIZE && !board[k][l])
		moves->push_back(AmazonMove{ pos, Position(k, l) });

	// go up;
	k = pos.x;
	l = pos.y;
	while (k-- > 0 && !board[k][l]) //while not 0 (aka not false)
		moves->push_back(AmazonMove{ pos, Position(k, l) });

	// go right;
	k = pos.x;
	l = pos.y;
	while (++l < c::BOARD_SIZE && !board[k][l])
		moves->push_back(AmazonMove{ pos, Position(k, l) });

	// go left;
	k = pos.x;
	l = pos.y;
	while (l-- > 0 && !board[k][l])
		moves->push_back(AmazonMove{ pos, Position(k, l) });

	// go down rigth;
	k = pos.x;
	l = pos.y;
	while (++k < c::BOARD_SIZE && ++l < c::BOARD_SIZE && !board[k][l])
		moves->push_back(AmazonMove{ pos, Position(k, l) });

	// go down left;
	k = pos.x;
	l = pos.y;
	while (++k < c::BOARD_SIZE && l-- > 0 && !board[k][l])
		moves->push_back(AmazonMove{ pos, Position(k, l) });

	// go up rigth;
	k = pos.x;
	l = pos.y;
	while (k-- > 0 && ++l < c::BOARD_SIZE && !board[k][l])
		moves->push_back(AmazonMove{ pos, Position(k, l) });

	// go up left;
	k = pos.x;
	l = pos.y;
	while (k-- > 0 && l-- > 0 && !board[k][l])
		moves->push_back(AmazonMove{ pos, Position(k, l) });
}

// find all possible moves from a position
std::vector<AmazonMove> Board::findAllMovesFrom(Position pos)
{

	std::vector<AmazonMove> moves;
	moves.reserve(9);

	int k;
	int l;

	// go down;
	k = pos.x;
	l = pos.y;
	while (++k < c::BOARD_SIZE && !board[k][l])
		moves.push_back(AmazonMove{ pos, Position(k, l) });

	// go up;
	k = pos.x;
	l = pos.y;
	while (k-- > 0 && !board[k][l]) //while not 0 (aka not false)
		moves.push_back(AmazonMove{ pos, Position(k, l) });

	// go right;
	k = pos.x;
	l = pos.y;
	while (++l < c::BOARD_SIZE && !board[k][l])
		moves.push_back(AmazonMove{ pos, Position(k, l) });

	// go left;
	k = pos.x;
	l = pos.y;
	while (l-- > 0 && !board[k][l])
		moves.push_back(AmazonMove{ pos, Position(k, l) });

	// go down rigth;
	k = pos.x;
	l = pos.y;
	while (++k < c::BOARD_SIZE && ++l < c::BOARD_SIZE && !board[k][l])
		moves.push_back(AmazonMove{ pos, Position(k, l) });

	// go down left;
	k = pos.x;
	l = pos.y;
	while (++k < c::BOARD_SIZE && l-- > 0 && !board[k][l])
		moves.push_back(AmazonMove{ pos, Position(k, l) });

	// go up rigth;
	k = pos.x;
	l = pos.y;
	while (k-- > 0 && ++l < c::BOARD_SIZE && !board[k][l])
		moves.push_back(AmazonMove{ pos, Position(k, l) });

	// go up left;
	k = pos.x;
	l = pos.y;
	while (k-- > 0 && l-- > 0 && !board[k][l])
		moves.push_back(AmazonMove{ pos, Position(k, l) });

	return moves;
}

//Same as findAllMoves but only counting instead putting into array
int Board::countAllMoves(int teamColor)
{
	int movesCount = 0;

	if (teamColor == WHITES)
		for (int i = 0; i < wAmazonsPositions.size(); i++)
			countAllMovesFrom(wAmazonsPositions[i], &movesCount);
	else if (teamColor == BLACKS)
		for (int i = 0; i < bAmazonsPositions.size(); i++)
			countAllMovesFrom(bAmazonsPositions[i], &movesCount);

	/*for (int i = 0; i < c::BOARD_SIZE; i++)
		for (int j = 0; j < c::BOARD_SIZE; j++)
			if (board[i][j] == teamColor)
			{
				countAllMovesFrom(Position(i, j), &movesCount);
			}*/

	return movesCount;
}

// find all possible moves from a position
int Board::countAllMovesFrom(Position pos, int *movesCount)
{
	if (!movesCount)
		(*movesCount) = 0;

	int k;
	int l;

	// go down;
	k = pos.x;
	l = pos.y;
	while (++k < c::BOARD_SIZE && !board[k][l])
		(*movesCount)++;

	// go up;
	k = pos.x;
	l = pos.y;
	while (k-- > 0 && !board[k][l]) //while not 0 (aka not false)
		(*movesCount)++;

	// go right;
	k = pos.x;
	l = pos.y;
	while (++l < c::BOARD_SIZE && !board[k][l])
		(*movesCount)++;

	// go left;
	k = pos.x;
	l = pos.y;
	while (l-- > 0 && !board[k][l])
		(*movesCount)++;

	// go down rigth;
	k = pos.x;
	l = pos.y;
	while (++k < c::BOARD_SIZE && ++l < c::BOARD_SIZE && !board[k][l])
		(*movesCount)++;

	// go down left;
	k = pos.x;
	l = pos.y;
	while (++k < c::BOARD_SIZE && l-- > 0 && !board[k][l])
		(*movesCount)++;

	// go up rigth;
	k = pos.x;
	l = pos.y;
	while (k-- > 0 && ++l < c::BOARD_SIZE && !board[k][l])
		(*movesCount)++;

	// go up left;
	k = pos.x;
	l = pos.y;
	while (k-- > 0 && l-- > 0 && !board[k][l])
		(*movesCount)++;

	return *movesCount;
}

int** Board::getAmazons()
{
	int** amazons = 0;
	amazons = new int* [c::AMAZONS];
	int count = 0;
	for (int i = 0; i < c::BOARD_SIZE; i++)
		for (int j = 0; j < c::BOARD_SIZE; j++)
			if (board[i][j] == WHITES || board[i][j] == BLACKS)
			{
				// it should be 8 amazons (ar as much as c::AMAZONS defines) so array gets filled and not overfilled
				amazons[count] = new int[] {board[i][j], i, j}; // amazon type and it's position
				count++;
			}
	return amazons;
}

void Board::setAmazonsArrays() 
{
	wAmazonsPositions.clear();
	bAmazonsPositions.clear();

	for (int i = 0; i < c::BOARD_SIZE; i++)
		for (int j = 0; j < c::BOARD_SIZE; j++)
			if (board[i][j] == WHITES)
				wAmazonsPositions.push_back(Position(i, j));
			else if (board[i][j] == BLACKS)
				bAmazonsPositions.push_back(Position(i, j));
}


int** Board::getAmazons(int teamColor)
{
	int** amazons = 0;
	amazons = new int* [c::AMAZONS/2]; //one player has 4 or half of the amazons on the board
	int count = 0;
	for (int i = 0; i < c::BOARD_SIZE * c::BOARD_SIZE; i++)
		if (board[i / c::BOARD_SIZE][i % c::BOARD_SIZE] == teamColor)
		{
			// it should be 4 amazons (ar half of what c::AMAZONS defines) so array gets filled and not overfilled
			amazons[count] = new int[] {i / c::BOARD_SIZE, i % c::BOARD_SIZE}; // amazon position (caller knows the type (teamColor)
			count++;
		}
	return amazons;
}

bool Board::isMoveAllowed(Position oldPos, Position newPos)
{
	if (!isQueenTrajectory(oldPos, newPos))
		return false;

	if (!isOnBoard(newPos))
		return false;

	int y = oldPos.y;
	int x = oldPos.x;
	int yNew = newPos.y;
	int xNew = newPos.x;

	int dk, dl;
	if (x < xNew)
		dk = 1;
	else if (x > xNew)
		dk = -1;
	else
		dk = 0;

	if (y < yNew)
		dl = 1;
	else if (y > yNew)
		dl = -1;
	else
		dl = 0;
	do
	{
		x += dk;
		y += dl;
		if (board[x][y] != 0)
			return false;
	} while (x != xNew || y != yNew);
	return true;
}		  

inline bool Board::isQueenTrajectory(Position oldPos, Position newPos)
{
	int dx = abs(newPos.x - oldPos.x);
	int dy = abs(newPos.y - oldPos.y);
	if (dx == 0 && dy == 0)
		return false; // can't move to the same position
	if (dx == 0 || dy == 0)
		return true;  // left/right or up/down move
	if (dx == dy)
		return true;  // diagonal move
	return false; // all other cases are not allowed
}

/// <summary>
/// Is pos position on the chess board (such field in board 2d array exists)?
/// Pasticulary important because in C++ if we have int[5][5] a, a[2][5] works and points to a[3][0]
/// </summary>
/// <param name="pos"></param>
/// <returns></returns>
inline bool Board::isOnBoard(Position pos)
{
	if (pos.x < 0 || pos.x >= c::BOARD_SIZE)
		return false; // pos is either above or below board
	if (pos.y < 0 || pos.y >= c::BOARD_SIZE)
		return false; // pos is either to the left or right from the board
	return true; // not above, not below, not too left or too right - pos is on the board
}
// returns true if given player has at least one possible move with any of his amazons
bool Board::hasMove(int teamColor)
{
	for (int i = 0; i < c::BOARD_SIZE; i++)
		for (int j = 0; j < c::BOARD_SIZE; j++)
			if (board[i][j] == teamColor)
			{
				if (hasMove(Position(i, j)))
					return true;
			}
	return false;
}

// returns true if given amazon has at least one possible move
bool Board::hasMove(Position amazon)
{
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
		{
			// if (i == j == 0)      //TODO: investigate seems compare i and j, then the result (boolean) compares with 0. So if j != i -> false == false -> true
			if (i == 0 && j == 0) //the spot amazon is standing. Not necessary since it is always not true
				continue;
			int x = amazon.x + i;
			int y = amazon.y + j;
			if ((x < 0 || x >= c::BOARD_SIZE) || (y < 0 || y >= c::BOARD_SIZE))
				continue;		  // space is not on the board
			if (board[x][y] == 0) // is space empty
				return true;
		}
	return false;
}

int Board::allPossibleDirections(int teamColor) 
{
	int directionsCount = 0;

	if (teamColor == WHITES)
		for (int i = 0; i < wAmazonsPositions.size(); i++)
			directionsCount += possibleDirections(wAmazonsPositions[i]);
	else if (teamColor == BLACKS)
		for (int i = 0; i < bAmazonsPositions.size(); i++)
			directionsCount += possibleDirections(bAmazonsPositions[i]);

	return directionsCount;
}

int Board::possibleDirections(Position amazon)
{
	int directions = 0;
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
		{
			// if (i == j == 0)      //TODO: investigate seems compare i and j, then the result (boolean) compares with 0. So if j != i -> false == false -> true
			if (i == 0 && j == 0) //the spot amazon is standing. Not necessary since it is always not true
				continue;
			int x = amazon.x + i;
			int y = amazon.y + j;
			if ((x < 0 || x >= c::BOARD_SIZE) || (y < 0 || y >= c::BOARD_SIZE))
				continue;		  // space is not on the board
			if (board[x][y] == 0) // is space empty
				directions ++;
		}
	return directions;
}

void Board::moveAmazon(Position oldPos, Position newPos)
{
	//TODO error prevention, maybe exception? if newPos is out of bounds
	board[newPos.x][newPos.y] = board[oldPos.x][oldPos.y]; // move amazon
	board[oldPos.x][oldPos.y] = 0; // empty old place

	for(int i = 0; i< wAmazonsPositions.size(); i++)
		if (wAmazonsPositions[i] == oldPos)
		{
			wAmazonsPositions[i] = newPos;
			return;
		}
	for (int i = 0; i < bAmazonsPositions.size(); i++)
		if (bAmazonsPositions[i] == oldPos)
		{
			bAmazonsPositions[i] = newPos;
			return;
		}
	throw "Wrong amazon position!";
}







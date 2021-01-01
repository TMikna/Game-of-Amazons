#include "Board.h"
#include <iostream>

    
Board::Board()
{
    //window.create(VideoMode(600, 600), "TheChess!");
}

std::vector<AmazonMove> Board::findAllMoves(int teamColor)
{
	std::vector<AmazonMove> moves;

	for (int i = 0; i < c::BOARD_SIZE; i++)
		for (int j = 0; j < c::BOARD_SIZE; j++)
			if (board[i][j] == teamColor)
			{
				findAllMovesFrom(Vector2i(i, j), &moves);
			}

	return moves;
}

// find all possible moves from a position
std::vector<AmazonMove>* Board::findAllMovesFrom(Vector2i pos, std::vector<AmazonMove> *moves)
{
	if (!moves)
		moves = new std::vector<AmazonMove>;

	int k;
	int l;

	// go down;
	k = pos.x;
	l = pos.y;
	while (++k < c::BOARD_SIZE && !board[k][l])
		moves->push_back(AmazonMove{ pos, Vector2i(k, l) });

	// go up;
	k = pos.x;
	l = pos.y;
	while (k-- > 0 && !board[k][l]) //while not 0 (aka not false)
		moves->push_back(AmazonMove{ pos, Vector2i(k, l) });

	// go right;
	k = pos.x;
	l = pos.y;
	while (++l < c::BOARD_SIZE && !board[k][l])
		moves->push_back(AmazonMove{ pos, Vector2i(k, l) });

	// go left;
	k = pos.x;
	l = pos.y;
	while (l-- > 0 && !board[k][l])
		moves->push_back(AmazonMove{ pos, Vector2i(k, l) });

	// go down rigth;
	k = pos.x;
	l = pos.y;
	while (++k < c::BOARD_SIZE && ++l < c::BOARD_SIZE && !board[k][l])
		moves->push_back(AmazonMove{ pos, Vector2i(k, l) });

	// go down left;
	k = pos.x;
	l = pos.y;
	while (++k < c::BOARD_SIZE && l-- > 0 && !board[k][l])
		moves->push_back(AmazonMove{ pos, Vector2i(k, l) });

	// go up rigth;
	k = pos.x;
	l = pos.y;
	while (k-- > 0 && ++l < c::BOARD_SIZE && !board[k][l])
		moves->push_back(AmazonMove{ pos, Vector2i(k, l) });

	// go up left;
	k = pos.x;
	l = pos.y;
	while (k-- > 0 && l-- > 0 && !board[k][l])
		moves->push_back(AmazonMove{ pos, Vector2i(k, l) });

	return moves;
}

//Same as findAllMoves but only counting instead putting into array
int Board::countAllMoves(int teamColor)
{
	int movesCount = 0;

	for (int i = 0; i < c::BOARD_SIZE; i++)
		for (int j = 0; j < c::BOARD_SIZE; j++)
			if (board[i][j] == teamColor)
			{
				countAllMovesFrom(Vector2i(i, j), &movesCount);
			}

	return movesCount;
}

// find all possible moves from a position
int Board::countAllMovesFrom(Vector2i pos, int *movesCount)
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

bool Board::isMoveAllowed(Vector2i oldPos, Vector2i newPos)
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

inline bool Board::isQueenTrajectory(Vector2i oldPos, Vector2i newPos)
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
inline bool Board::isOnBoard(Vector2i pos)
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
				if (hasMove(Vector2i(i, j)))
					return true;
			}
	return false;
}

// returns true if given amazon has at least one possible move
bool Board::hasMove(Vector2i amazon)
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

void Board::moveAmazon(Vector2i oldPos, Vector2i newPos)
{
	//TODO error prevention, maybe exception? if newPos is out of bounds
	board[newPos.x][newPos.y] = board[oldPos.x][oldPos.y]; // move amazon
	board[oldPos.x][oldPos.y] = 0; // empty old place
}

void Board::moveAmazon(AmazonMove move)
{
	moveAmazon(move.from, move.to);
}







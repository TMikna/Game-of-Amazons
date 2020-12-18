#include "Board.h"
#include <iostream>


    
Board::Board()
{
    //window.create(VideoMode(600, 600), "TheChess!");
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

bool Board::isMoveAllowed(Vector2i oldPos, Vector2i newPos)
{
	if (!isQueenTrajectory(oldPos, newPos))
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

void Board::moveAmazon(Vector2i oldPos, Vector2i newPos)
{
	board[newPos.x][newPos.y] = board[oldPos.x][oldPos.y]; // move amazon
	board[oldPos.x][oldPos.y] = 0; // empty old place
}





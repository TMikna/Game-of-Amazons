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
				// it should be 8 queens so array gets filled and not overfilled
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



/*
* to write move coordinates as a string
std::string Board::toChessNote(Vector2f p)
{
	std::string s = "";
	s += char(p.x / SQUARE_SIZE + 97);
	s += std::to_string((int)(9 - p.y / SQUARE_SIZE));  //counting squeres 1-10, would be better 0-9?
	return s;
}

Vector2f toCoord(char a, char b)
{
	int x = int(a) - 97;
	int y = 9 - int(b) + 49;
	return Vector2f(x * SQUARE_SIZE, y * SQUARE_SIZE);
}
*/



/*

OLD CODE

#include "Board.h"
#include <iostream>



Board::Board()
{
	window.create(VideoMode(600, 600), "TheChess!");
}
void Board::loadBoard(std::string boardPath, std::string queensPath, std::string arrowPath)
{
	tBoard.loadFromFile(boardPath);
	sBoard.setTexture(tBoard, true);

	tQueens.loadFromFile(queensPath);
	loadQueens();

	tArrow.loadFromFile(arrowPath);
	loadArrows();
};

void Board::display()
{
	window.clear();
	window.draw(sBoard);
	for (int i = 0; i < 8; i++)
		window.draw(sQueens[i]);
	for (int i = 0; i < arrowCount; i++)
		window.draw(sArrows[i]);
	window.display();
}

void Board::loadQueens()
{
	for (int i = 0; i < 8; i++)
		sQueens[i].setTexture(tQueens);

	int k = 0;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
		{
			int n = board[i][j];
			if (!n)
				continue;
			sQueens[k].setTextureRect(IntRect(0, SQUARE_SIZE * (n%2), SQUARE_SIZE, SQUARE_SIZE));
			sQueens[k].setPosition(SQUARE_SIZE * j, SQUARE_SIZE * i);
			k++;
		}
	//for (int i = 0; i < position.length(); i += 5)
	//	move(position.substr(i, 4));
}

void Board::loadArrows()
{
	for (int i = 0; i < 92; i++)
	{
		sArrows[i].setTexture(tArrow);
		sArrows[i].setPosition(-100, -100);
	}
}

bool Board::startMove(Vector2i mousePos, int player)
{
	for (int i = 0; i < 8; i++)
		if (sQueens[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
		{
			oldPos = sQueens[i].getPosition();
			//if player try to move other player queen / not his turn
			if (getPlayer(oldPos) != player)
				return false;
			n = i;
			dx = mousePos.x - sQueens[i].getPosition().x;
			dy = mousePos.y - sQueens[i].getPosition().y;
			return true;
		}
	return false;
}
bool Board::finishMoving()
{
	Vector2f p = sQueens[n].getPosition() + Vector2f(SQUARE_SIZE / 2, SQUARE_SIZE / 2);
	newPos = Vector2f(SQUARE_SIZE * int(p.x / SQUARE_SIZE), SQUARE_SIZE * int(p.y / SQUARE_SIZE));
	// if queen dropped to the same osition - move is cancelled
	if (newPos == oldPos)
	{
		sQueens[n].setPosition(oldPos);
		return false;
	}
	// not allowed move
	if (!isMoveAllowd(oldPos, newPos))
	{
		sQueens[n].setPosition(oldPos);
			return false;
	}

	//str = toChessNote(oldPos) + toChessNote(newPos);
	//move(oldPos, newPos);
	//position += str + " ";
	//std::cout << str << std::endl;
	moveAmazon(oldPos, newPos);
	return true;
}

void Board::setAmazonPosition(Vector2i mousePos)
{
	sQueens[n].setPosition(mousePos.x - dx, mousePos.y - dy);
}

bool Board::shootArrow(Vector2i mousePos)
{
	//if (arrowCount < MAX_ARROWS) TODO: error prevention
	Vector2f arrowPos = Vector2f(SQUARE_SIZE * int(mousePos.x / SQUARE_SIZE), SQUARE_SIZE * int(mousePos.y / SQUARE_SIZE));

	if (!isMoveAllowd(newPos, arrowPos))
		return false;

	placeArrow(arrowPos);

	return true;
}
inline void Board::placeArrow(Vector2f pos)
{
	int l = int(pos.x / SQUARE_SIZE);
	int k = int(pos.y / SQUARE_SIZE);
	board[k][l] = -1;

	sArrows[arrowCount].setPosition(pos.x, pos.y);
	arrowCount++;
}

inline bool Board::isMoveAllowd(Vector2f oldPos, Vector2f newPos)
{
	if (!isQueenTrajectory(oldPos, newPos))
		return false;
	int l = int(oldPos.x / SQUARE_SIZE);
	int k = int(oldPos.y / SQUARE_SIZE);
	int lNew = int(newPos.x / SQUARE_SIZE);
	int kNew = int(newPos.y / SQUARE_SIZE);

	int dk, dl;
	if (k < kNew)
		dk = 1;
	else if (k > kNew)
		dk = -1;
	else
		dk = 0;

	if (l < lNew)
		dl = 1;
	else if (l > lNew)
		dl = -1;
	else
		dl = 0;
	do
	{
		k += dk;
		l += dl;
		if (board[k][l] != 0)
			return false;
	} while (k != kNew || l != lNew);
	return true;
}

inline bool Board::isQueenTrajectory(Vector2f oldPos, Vector2f newPos)
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

void Board::moveAmazon(Vector2f oldPos, Vector2f newPos)
{
	int l = int(oldPos.x / SQUARE_SIZE);
	int k = int(oldPos.y / SQUARE_SIZE);
	int lNew = int(newPos.x / SQUARE_SIZE);
	int kNew = int(newPos.y / SQUARE_SIZE);

	board[kNew][lNew] = board[k][l];
	board[k][l] = 0;

	// set position for UI
	sQueens[n].setPosition(newPos);
}

inline int Board::getPlayer(Vector2f pos)
{
	// must ensure in pos place is an amazon, othervise return 0 for empty or -1 for arrow
	return board[int(pos.y / SQUARE_SIZE)][int(pos.x / SQUARE_SIZE)];
}




/*
* to write move coordinates as a string
std::string Board::toChessNote(Vector2f p)
{
	std::string s = "";
	s += char(p.x / SQUARE_SIZE + 97);
	s += std::to_string((int)(9 - p.y / SQUARE_SIZE));  //counting squeres 1-10, would be better 0-9?
	return s;
}

Vector2f toCoord(char a, char b)
{
	int x = int(a) - 97;
	int y = 9 - int(b) + 49;
	return Vector2f(x * SQUARE_SIZE, y * SQUARE_SIZE);
}
*/





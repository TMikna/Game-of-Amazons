#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"

using namespace sf;

class Board
{
public:
    RenderWindow window;

    Board();
    void moveAmazon(Vector2i oldPos, Vector2i newPos);
    bool isMoveAllowed(Vector2i oldPos, Vector2i newPos);
    void placeArrow(Vector2i pos) { board[pos.x][pos.y] = -1; };
    int getPlayer(Vector2i pos) { return board[pos.x][pos.y]; };
    int** getAmazons();

private:
    int board[10][10] =
    { 0, 0, 0, 2, 0, 0, 2, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      2, 0, 0, 0, 0, 0, 0, 0, 0, 2,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 1, 0, 0, 1, 0, 0, 0 };

    bool isQueenTrajectory(Vector2i oldPos, Vector2i newPos);
};
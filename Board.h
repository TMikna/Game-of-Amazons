#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "AmazonMove.cpp"
#include <array>

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
    int** getAmazons(int teamColor);
    std::vector<AmazonMove> findAllMoves(int teamColor); //find all allowd player amazons moves (from Vector2i[0] to Vector2i[1])
    std::vector<AmazonMove>* findAllMovesFrom(Vector2i pos, std::vector<AmazonMove> *moves = NULL);


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

    //int board[c::BOARD_SIZE][c::BOARD_SIZE] =
    //{ 0, 0, 2, 2,
    //  0, 0, 0, 0,
    //  1, 0, 0, 0,
    //  0, 0, 0, 1 };

    bool isQueenTrajectory(Vector2i oldPos, Vector2i newPos);
};
#pragma once
#include "Constants.h"
#include "AmazonMove.h"
#include <array>
#include <deque>


using namespace sf;

class Board
{
public:

    RenderWindow window;

    Board() { setAmazonsArrays(); };
    Board(BoardArray boardState) { this->board = boardState; setAmazonsArrays(); };
    void moveAmazon(Vector2i oldPos, Vector2i newPos);
    bool isMoveAllowed(Vector2i oldPos, Vector2i newPos);
    void placeArrow(Vector2i pos) { board[pos.x][pos.y] = -1; };
    void undoArrow(Vector2i pos) { board[pos.x][pos.y] = 0; };
    int getPlayer(Vector2i pos) { return board[pos.x][pos.y]; };
    int** getAmazons();
    int** getAmazons(int teamColor);
    int possibleDirections(Vector2i amazon);
    int allPossibleDirections(int teamColor);


    //All moves finding is a bit messy, might be nicer if I saves queens in separate arrays too, but for now decided to leave all logic on board array
    //Probably it's still possible to implement it nicer

//    std::vector<AmazonMove> findAllMoves(int teamColor); //find all allowd player amazons moves (from Vector2i[0] to Vector2i[1])
    std::vector<AmazonMove> findAllMoves(int teamColor); //find all allowd player amazons moves (from Vector2i[0] to Vector2i[1])
//    std::vector<AmazonMove> findAllMovesFrom(Vector2i pos, std::vector<AmazonMove>* moves = NULL);
    std::vector<AmazonMove> findAllMovesFrom(Vector2i pos);
    int countAllMoves(int teamColor);  // same as finding, but instead counting only (for performance improvement)
    int countAllMovesFrom(Vector2i pos, int *movesCount = NULL);

    bool hasMove(int teamColor);
    bool hasMove(Vector2i amazon);

    void printBoard();

    BoardArray getBoardState() { return board; };
    //currently unused
    void setBoardState(BoardArray board) { this->board = board; setAmazonsArrays();
    };

private:
    BoardArray board = init::INITIAL_BOARD;

    std::vector<Vector2i> wAmazonsPositions;
    std::vector<Vector2i> bAmazonsPositions;

    void setAmazonsArrays();
    bool isQueenTrajectory(Vector2i oldPos, Vector2i newPos);
    inline bool isOnBoard(Vector2i pos);
    inline void findAllMovesFrom(Vector2i pos, std::vector<AmazonMove>* moves); //for findAllMoves method
     
};



#pragma once
#include "Constants.h"
#include "AmazonMove.h"
#include <array>
#include <deque>
#include <vector>

class Board
{
public:

    Board() { setAmazonsArrays(); };
    Board(BoardArray boardState) { this->board = boardState; setAmazonsArrays(); };
    void moveAmazon(Position oldPos, Position newPos);
    bool isMoveAllowed(Position oldPos, Position newPos);
    void placeArrow(Position pos) { board[pos.x][pos.y] = -1; };
    void undoArrow(Position pos) { board[pos.x][pos.y] = 0; };
    int getPlayer(Position pos) { return board[pos.x][pos.y]; };
    int** getAmazons();
    int** getAmazons(int teamColor);
    int possibleDirections(Position amazon);
    int allPossibleDirections(int teamColor);


    //All moves finding is a bit messy, might be nicer if I saves queens in separate arrays too, but for now decided to leave all logic on board array
    //Probably it's still possible to implement it nicer

//    std::vector<AmazonMove> findAllMoves(int teamColor); //find all allowd player amazons moves (from Position[0] to Position[1])
    std::vector<AmazonMove> findAllMoves(int teamColor); //find all allowd player amazons moves (from Position[0] to Position[1])
//    std::vector<AmazonMove> findAllMovesFrom(Vector2i pos, std::vector<AmazonMove>* moves = NULL);
    std::vector<AmazonMove> findAllMovesFrom(Position pos);
    int countAllMoves(int teamColor);  // same as finding, but instead counting only (for performance improvement)
    int countAllMovesFrom(Position pos, int *movesCount = NULL);

    bool hasMove(int teamColor);
    bool hasMove(Position amazon);

    void printBoard();

    BoardArray getBoardState() { return board; };
    //currently unused
    void setBoardState(BoardArray board) { this->board = board; setAmazonsArrays();
    };

private:
    BoardArray board = init::INITIAL_BOARD;

    std::vector<Position> wAmazonsPositions;
    std::vector<Position> bAmazonsPositions;

    void setAmazonsArrays();
    bool isQueenTrajectory(Position oldPos, Position newPos);
    inline bool isOnBoard(Position pos);
    inline void findAllMovesFrom(Position pos, std::vector<AmazonMove>* moves); //for findAllMoves method
     
};



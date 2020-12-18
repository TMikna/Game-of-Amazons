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
    /*std::string toChessNote(Vector2f p);
    * 
    */
};



/*
OLD CODE


#ifndef BOARD_H
#define BOARD_H
#endif

#include <SFML/Graphics.hpp>

using namespace sf;

class BoardOld
{
public:
    RenderWindow window;

    Board();
    void loadBoard();
    void display();
    /// <summary>
    /// returns true if move was started of false of no (e.g. click was not on an amazon)
    /// </summary>
    /// <param name="mousePos"></param>
    bool startMove(Vector2i mousePos, int player);
    bool finishMoving();
    void setAmazonPosition(Vector2i mousePos);
    bool shootArrow(Vector2i mousePos);

    Sprite getBoardSprite() { return sBoard; };


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

    /// <summary>
    /// One square size in pixels
    /// </summary>
    const int SQUARE_SIZE = 60;
    const int MAX_ARROWS = 92;

    int arrowCount = 0;
    Texture tBoard, tQueens, tArrow;
    Sprite sBoard, sQueens[8], sArrows[92];

    std::string position = "";  // current possition (all moves history)

    // Move variables:
    int n;
    float dx, dy;
    Vector2f oldPos, newPos;
    std::string str;

    void moveAmazon(Vector2f oldPos, Vector2f newPos);
    inline void placeArrow(Vector2f pos);
    bool isMoveAllowd(Vector2f oldPos, Vector2f newPos);
    bool isQueenTrajectory(Vector2f oldPos, Vector2f newPos);
    void loadQueens(); // Load starting queens positiomn
    void loadArrows(); // Load and prepare arrows for later use
    inline int getPlayer(Vector2f pos);
    /*std::string toChessNote(Vector2f p);
    *
    
};





*/
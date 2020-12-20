#pragma once

#define WHITES 1   // white figures; 1st player figures
#define BLACKS 2   // black figures; 2nd player figures
// general constants
namespace c
{
    //const int BOARD_SIZE = 10;
    //const int AMAZONS = 8;       // total amount of amazons on the board. Should be 8 unless board in board class is changed. must be divisible by 2
    //const int MAX_ARROWS = 92;  // max possible amount of arrows on the board. Amount of board squares - QUEESNS. 92 on a standart 10x10 board

    const int BOARD_SIZE = 4;
    const int AMAZONS = 4;       // total amount of amazons on the board. Should be 8 unless board in board class is changed. must be divisible by 2
    const int MAX_ARROWS = 12;  // max possible amount of arrows on the board. Amount of board squares - QUEESNS. 92 on a standart 10x10

} 
    
// constants for UI, mostly related to window size
namespace cUI
{
    // one squere on board size (width or heigth) in pixels
    const int SQUARE_SIZE = 60;

    const int BOARD_WIDTH = 600;  //SQUARE_SIZE*BOARD_SIZE + possible offset (sides etc);
    const int BOARD_HEIGHT = 600; //SQUARE_SIZE*BOARD_SIZE + possible offset (sides etc);

    const int WIN_MSG_WIDTH = 300;
    const int WIN_MSG_HEIGHT = 50;
}
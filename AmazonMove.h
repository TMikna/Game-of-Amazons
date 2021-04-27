#pragma once

#include <stdint.h>

struct Position
{
    /// Creates a Vector2(0, 0).
    Position() { x = 0; y = 0; }
    Position(int_fast8_t X, int_fast8_t Y) { x = X; y = Y; }

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    int_fast8_t x; ///< X coordinate of the vector
    int_fast8_t y; ///< Y coordinate of the vector
    
    bool operator == (Position const& pos) {
    if (pos.x == x && pos.y == y)
        return true;
    return false;
    }
};





struct AmazonMove
{
    Position from;
    Position to;
};
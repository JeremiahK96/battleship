#include "global.hpp"

#include <cassert>

bool global::CoordinateInBounds (int coord)
{
    return coord >= 0 && coord < board_width * board_height;
}

void global::DoAsserts ()
{
    assert(CoordinateInBounds(0));
    assert(!CoordinateInBounds(-1));
    assert(CoordinateInBounds(board_width * board_height - 1));
    assert(!CoordinateInBounds(board_width * board_height));
}

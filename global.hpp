#pragma once

namespace global
{
    void DoAsserts ();

    inline const unsigned int board_width = 10;
    inline const unsigned int board_height = 10;
    inline const unsigned int board_area = board_height * board_width;

    inline const unsigned int ship_sizes[] = { 5, 4, 3, 3, 2 };

    bool CoordinateInBounds (int coord);
}

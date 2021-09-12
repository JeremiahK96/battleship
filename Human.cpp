#include "Player.hpp"
#include "global.hpp"

#include <iostream>
#include <string>

void Human::PlaceShips()
{
    ClearBoard();
    DisplayBoard();

    // Display ship to add.
    // Query position to place ship.
    // Query direction of ship (north, south, east, west).
    // Verify ship placement does not overlap other ships or run off the board.
    // Add ship to ship-board.
    // Repeat for all ships.
}

void Human::DisplayBoard ()
{
    // Draw top row with numerical labels.
    std::cout << "\n ";
    for (int i = 0; i < global::board_width; ++i)
        std::cout << ' ' << i + 1;
    std::cout << '\n';

    // Draw each board row with alpha label on left.
    for (int y = 0; y < global::board_height; ++y)
    {
        std::cout << char(y + 'A');

        for (int x = 0; x < global::board_height; ++x)
            std::cout << ' ' << GetCharAtPos(y * global::board_width + x);
        std::cout << '\n';
    }
    std::cout << '\n';
}

char Human::GetCharAtPos (int pos)
{
    return "./^v><"[board.at(pos)];
}

#include "Player.hpp"
#include "global.hpp"

#include <cassert>
#include <stdexcept>

void Player::ClearBoard ()
{
    while (!board.empty())
        board.pop_back();
    assert(board.empty());

    for (int i = 0; i < global::board_area; ++i)
        board.push_back(TL_EMPTY);
    assert(board.size() == global::board_area);
}

bool Player::ShipOrientationIsValid (
        int pos, Player::ship_direction dir, int ship_len)
{
    int delta;

    switch (dir)
    {
        case NORTH:
            delta = -global::board_width;
            break;

        case SOUTH:
            delta = global::board_width;
            break;

        case EAST:
            delta = 1;
            break;

        case WEST:
            delta = -1;
            break;

        default:
            throw std::logic_error("invalid ship_direction value in bool Player::ShipOrientationIsValid(int, Player::ship_direction, int)");
    }

    for (int i = 0; i < ship_len; ++i)
    {
        int coord = pos + delta * i;
        if (!global::CoordinateInBounds(coord) || board.at(coord) != TL_EMPTY)
            return false;
    }

    return true;
}

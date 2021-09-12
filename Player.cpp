#include "Player.hpp"
#include "global.hpp"

#include <cassert>
#include <iostream>
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

int Player::GetShipDelta(Player::ship_direction dir)
{
    switch (dir)
    {
        case NORTH: return -global::board_width;
        case SOUTH: return global::board_width;
        case EAST:  return 1;
        case WEST:  return -1;
    }

    throw std::logic_error("invalid ship_direction value in int Player::GetShipDelta(Player::ship_direction dir)");
}

bool Player::ShipOrientationIsValid (
        int pos, Player::ship_direction dir, int ship_len)
{
    int delta = GetShipDelta(dir);

    for (int i = 0; i < ship_len; ++i)
    {
        int coord = pos + delta * i;
        if (!global::CoordinateInBounds(coord) || board.at(coord) != TL_EMPTY)
            return false;
    }

    return true;
}

void Player::AddShip (int pos, Player::ship_direction dir, int ship_len)
{
    int delta = GetShipDelta(dir);

    for (int i = 0; i < ship_len; ++i)
        board.at(pos + delta * i) = TL_VERTICAL;
}

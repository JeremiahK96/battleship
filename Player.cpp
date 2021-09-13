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

    // Disallow ships running off top/bottom of board or crossing other ships.
    for (int i = 0; i < ship_len; ++i)
    {
        int coord = pos + delta * i;
        if (!global::CoordinateInBounds(coord) || board.at(coord) != TL_EMPTY)
            return false;
    }

    // Disallow ships running off sides of board.
    if (dir == Player::EAST || dir == Player::WEST)
    {
        int bow_pos = pos + delta * (ship_len - 1);
        if (pos / global::board_width != bow_pos / global::board_width)
            return false;
    }

    return true;
}

void Player::AddShip (int pos, Player::ship_direction dir, int ship_len)
{
    tile stern;
    tile deck;
    tile bow;

    switch (dir)
    {
        case NORTH: stern   = TL_NORTH;
                    deck    = TL_VERTICAL;
                    bow     = TL_SOUTH;
                    break;

        case SOUTH: stern   = TL_SOUTH;
                    deck    = TL_VERTICAL;
                    bow     = TL_NORTH;
                    break;

        case EAST:  stern   = TL_EAST;
                    deck    = TL_HORIZONTAL;
                    bow     = TL_WEST;
                    break;

        case WEST:  stern   = TL_WEST;
                    deck    = TL_HORIZONTAL;
                    bow     = TL_EAST;
                    break;
    }

    int delta = GetShipDelta(dir);
    for (int i = 1; i < ship_len - 1; ++i)
        board.at(pos + delta * i) = deck;

    board.at(pos) = stern;
    board.at(pos + delta * (ship_len - 1)) = bow;
}

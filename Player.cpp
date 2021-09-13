#include "Player.hpp"
#include "global.hpp"

#include <cassert>
#include <iostream>
#include <stdexcept>

void Player::ClearBoards ()
{
    while (!ships.empty())
        ships.pop_back();
    assert(ships.empty());

    for (int i = 0; i < global::board_area; ++i)
        ships.push_back(SHIP_EMPTY);
    assert(ships.size() == global::board_area);
}

int Player::GetShipDelta(Player::ship_dir dir)
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
        unsigned int pos, Player::ship_dir dir, unsigned int ship_len)
{
    int delta = GetShipDelta(dir);

    // Disallow ships running off top/bottom of board or crossing other ships.
    for (int i = 0; i < ship_len; ++i)
    {
        unsigned int coord = pos + delta * i;
        if (!global::CoordinateInBounds(coord) || ships.at(coord) != SHIP_EMPTY)
            return false;
    }

    // Disallow ships running off sides of board.
    if (dir == Player::EAST || dir == Player::WEST)
    {
        unsigned int bow_pos = pos + delta * (ship_len - 1);
        if (pos / global::board_width != bow_pos / global::board_width)
            return false;
    }

    return true;
}

void Player::AddShip (
        unsigned int pos, Player::ship_dir dir, unsigned int ship_len)
{
    ship stern;
    ship deck;
    ship bow;

    switch (dir)
    {
        case NORTH: stern   = SHIP_NORTH;
                    deck    = SHIP_VERTICAL;
                    bow     = SHIP_SOUTH;
                    break;

        case SOUTH: stern   = SHIP_SOUTH;
                    deck    = SHIP_VERTICAL;
                    bow     = SHIP_NORTH;
                    break;

        case EAST:  stern   = SHIP_EAST;
                    deck    = SHIP_HORIZONTAL;
                    bow     = SHIP_WEST;
                    break;

        case WEST:  stern   = SHIP_WEST;
                    deck    = SHIP_HORIZONTAL;
                    bow     = SHIP_EAST;
                    break;
    }

    int delta = GetShipDelta(dir);
    for (int i = 1; i < ship_len - 1; ++i)
        ships.at(pos + delta * i) = deck;

    ships.at(pos) = stern;
    ships.at(pos + delta * (ship_len - 1)) = bow;
}

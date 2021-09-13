#pragma once

#include "global.hpp"

#include <vector>

class Player
{
protected:
    enum ship {
        SHIP_EMPTY,
        SHIP_VERTICAL,
        SHIP_HORIZONTAL,
        SHIP_NORTH,
        SHIP_SOUTH,
        SHIP_EAST,
        SHIP_WEST
    };

    enum guess {
        NOGUESS,
        MISS,
        HIT
    };

    enum ship_dir {
        NORTH,
        SOUTH,
        EAST,
        WEST
    };

    std::vector<ship> ships;
    std::vector<guess> guesses;

    void ClearBoards ();

    virtual void PlaceShip (unsigned int ship_index) = 0;
    int GetShipDelta(Player::ship_dir dir);
    bool ShipOrientationIsValid (
            unsigned int pos,
            ship_dir dir,
            unsigned int ship_len);
    void AddShip (unsigned int pos, ship_dir dir, unsigned int ship_len);

public:
    virtual void PlaceShips () = 0;
};

class Human :
    public Player
{
protected:
    void DisplayShips ();
    char GetShipCharAtPos (unsigned int pos);
    unsigned int QueryCoordinate ();

    void PlaceShip (unsigned int ship_index);
    void DisplayShip (unsigned int ship_index);
    unsigned int GetShipPosition ();
    ship_dir GetShipDirection ();

public:
    void PlaceShips ();
};

class Computer :
    public Player
{
protected:
    void PlaceShip (unsigned int ship_index);

public:
    void PlaceShips ();
};

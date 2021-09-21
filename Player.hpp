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

    virtual void PlaceShip (const unsigned int ship_index) = 0;
    int GetShipDelta(const Player::ship_dir dir);
    bool ShipOrientationIsValid (
            const unsigned int pos,
            const ship_dir dir,
            const unsigned int ship_len);
    void AddShip (
            const unsigned int pos,
            const ship_dir dir,
            const unsigned int ship_len);

public:
    virtual void PlaceShips () = 0;
};

class Human :
    public Player
{
protected:
    void DisplayShips ();
    char GetShipCharAtPos (const unsigned int pos);
    unsigned int QueryCoordinate ();

    void PlaceShip (const unsigned int ship_index);
    void DisplayShip (const unsigned int ship_index);
    unsigned int GetShipPosition ();
    ship_dir GetShipDirection ();

public:
    void PlaceShips ();
};

class Computer :
    public Player
{
protected:
    void PlaceShip (const unsigned int ship_index);

public:
    void PlaceShips ();
};

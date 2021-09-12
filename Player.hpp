#pragma once

#include "global.hpp"

#include <vector>

class Player
{
protected:
    enum tile
    {
        TL_EMPTY,
        TL_VERTICAL,
        TL_HORIZONTAL,
        TL_NORTH,
        TL_SOUTH,
        TL_EAST,
        TL_WEST
    };
    std::vector<tile> board;
    void ClearBoard ();

    enum ship_direction
    {
        NORTH,
        SOUTH,
        EAST,
        WEST
    };
    virtual void PlaceShip (int ship_index) = 0;
    int GetShipDelta(Player::ship_direction dir);
    bool ShipOrientationIsValid (int pos, ship_direction dir, int ship_len);
    void AddShip (int pos, ship_direction dir, int ship_len);

public:
    virtual void PlaceShips () = 0;
};

class Human :
    public Player
{
protected:
    void DisplayBoard ();
    char GetCharAtPos (int pos);

    void PlaceShip (int ship_index);
    void DisplayShip (int ship_index);
    int QueryShipPosition ();
    ship_direction QueryShipDirection ();
    int QueryCoordinate ();

public:
    void PlaceShips ();
};

class Computer :
    public Player
{
protected:
    void PlaceShip (int ship_index);

public:
    void PlaceShips ();
};

#pragma once

#include "global.hpp"

#include <vector>

class Player
{
protected:
    enum tile
    {
        TL_EMPTY,
        TL_SHIP,
        TL_NORTH,
        TL_SOUTH,
        TL_EAST,
        TL_WEST
    };
    std::vector<tile> board;

    void ClearBoard ();

public:
    virtual void PlaceShips () = 0;
};

class Human :
    public Player
{
protected:
    void DisplayBoard ();
    char GetCharAtPos (int pos);

public:
    void PlaceShips ();
};

class Computer :
    public Player
{
public:
    void PlaceShips ();
};

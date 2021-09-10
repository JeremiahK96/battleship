#pragma once

#include "global.hpp"

#include <array>

class Player
{
protected:
    std::array<unsigned char, global::board_area> board;

public:
    virtual void PlaceShips () = 0;
};

class Human :
    public Player
{
protected:
    void display_ships ();

public:
    void PlaceShips ();
};

class Computer :
    public Player
{
public:
    void PlaceShips ();
};

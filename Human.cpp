#include "Player.hpp"
#include "global.hpp"

#include <iostream>
#include <string>

void Human::PlaceShips ()
{
    ClearBoards();
    DisplayShips();

    // num_ships = the number of elements in global::ship_sizes
    unsigned int num_ships
            = sizeof(global::ship_sizes) / sizeof(global::ship_sizes[0]);

    for (unsigned int i = 0; i < num_ships; ++i)
    {
        PlaceShip(i);
        DisplayShips();
    }
}

void Human::PlaceShip (const unsigned int ship_index)
{
    unsigned int pos;
    ship_dir dir;
    unsigned int ship_len = global::ship_sizes[ship_index];

    DisplayShip(ship_index);

    while (true)
    {
        pos = GetShipPosition();
        dir = GetShipDirection();

        if (ShipOrientationIsValid(pos, dir, ship_len))
            break;

        std::cout << "Invalid ship orientation, please try again.\n";
    }

    AddShip(pos, dir, ship_len);
}

void Human::DisplayShip (const unsigned int ship_index)
{
    unsigned int ship_length = global::ship_sizes[ship_index];

    std::cout
        << "Ship #" << ship_index + 1
        << ", length = " << ship_length << ": <";

    for (int i = 0; i < ship_length - 2; ++i)
        std::cout << '/';

    std::cout << ">\n";
}

unsigned int Human::GetShipPosition ()
{
    unsigned int coord;

    do
    {
        std::cout
            << "Enter the alphanumeric coordinate to position the ship on: ";

        coord = QueryCoordinate();
    }
    while (!global::CoordinateInBounds(coord) || ships.at(coord) != SHIP_EMPTY);

    return coord;
}

Player::ship_dir Human::GetShipDirection ()
{
    // North/South/East/West/Up/Down/Left/Right/Vertical/Horizontal
    std::string valid_chars = "NSEWUDLRVH";

    std::string input;
    unsigned char input_char = ' ';

    do
    {
        std::cout << "Enter the direction the ship should face: ";
        std::getline(std::cin, input);

        if (!input.empty())
            input_char = std::toupper(input.at(0));
    }
    while (valid_chars.find_first_of(input_char) == std::string::npos);
    // Loop until input_char can be found within valid_chars.

    switch (input_char)
    {
        case 'N': case 'U': case 'H':   return NORTH;
        case 'S': case 'D':             return SOUTH;
        case 'E': case 'R': case 'V':   return EAST;
        case 'W': case 'L':             return WEST;
    }

    throw std::logic_error("invalid user input accepted in Player::ship_direction Human::QueryShipDirection()");
}

unsigned int Human::QueryCoordinate ()
{
    std::string input;
    std::getline(std::cin, input);

    if (global::IsValidAlphaNumeric(input))
        return global::AlphaNumericToCoordinate(input);
    return -1;  // unsigned int, so -1 isn't -1, but is the max value.
}

void Human::DisplayShips ()
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
            std::cout << ' ' << GetShipCharAtPos(y * global::board_width + x);

        std::cout << '\n';
    }

    std::cout << '\n';
}

char Human::GetShipCharAtPos (const unsigned int pos)
{
    switch (ships.at(pos))
    {
        case SHIP_EMPTY:        return '.';
        case SHIP_VERTICAL:     return '/';
        case SHIP_HORIZONTAL:   return '\\';
        case SHIP_NORTH:        return 'v';
        case SHIP_SOUTH:        return '^';
        case SHIP_EAST:         return '<';
        case SHIP_WEST:         return '>';
    }

    throw std::logic_error("invalid tile value in char Human::GetShipCharAtPos(int pos)");
}

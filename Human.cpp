#include "Player.hpp"
#include "global.hpp"

#include <iostream>
#include <string>

void Human::PlaceShips ()
{
    ClearBoard();

    int num_ships = sizeof(global::ship_sizes) / sizeof(global::ship_sizes[0]);
    for (int i = 0; i < num_ships; ++i)
    {
        DisplayBoard();
        PlaceShip(i);
    }
}

void Human::PlaceShip (int ship_index)
{
    int pos;
    ship_direction dir;
    int ship_len = global::ship_sizes[ship_index];

    DisplayShip(ship_index);

    while (true)
    {
        pos = QueryShipPosition();
        dir =  QueryShipDirection();

        if (ShipOrientationIsValid(pos, dir, ship_len))
            break;

        std::cout << "Invalid ship orientation, please try again.\n";
    }

    AddShip(pos, dir, ship_len);
}

void Human::DisplayShip (int ship_index)
{
    int ship_length = global::ship_sizes[ship_index];

    std::cout
        << "Ship #" << ship_index + 1
        << ", length = " << ship_length << ": <";
    for (int i = 0; i < ship_length - 2; ++i)
        std::cout << '/';
    std::cout << ">\n";
}

int Human::QueryShipPosition ()
{
    int coord;
    do
    {
        std::cout
            << "Enter the alphanumeric coordinate to position the ship on: ";
        coord = QueryCoordinate();
    }
    while (!global::CoordinateInBounds(coord) || board.at(coord) != TL_EMPTY);

    return coord;
}

Player::ship_direction Human::QueryShipDirection ()
{
    // North/South/East/West/Up/Down/Left/Right/Vertical/Horizontal
    std::string valid_chars = "NSEWUDLRVH";
    unsigned char input_char = ' ';
    std::string input;

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

int Human::QueryCoordinate ()
{
    std::string input;
    std::getline(std::cin, input);
    if (input.length() < 2)
        return -1;

    unsigned char alpha = std::toupper(input.at(0));
    unsigned char digit = input.at(1);
    if (alpha < 'A' || alpha > char('A' + global::board_height - 1))
        return -1;
    if (digit < '1' || digit > '9')
        return -1;

    int x = std::stoi(input.substr(1)) - 1;
    if (x >= global::board_width)
        return -1;

    return x + int(alpha - 'A') * global::board_width;
}

void Human::DisplayBoard ()
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
            std::cout << ' ' << GetCharAtPos(y * global::board_width + x);
        std::cout << '\n';
    }
    std::cout << '\n';
}

char Human::GetCharAtPos (int pos)
{
    switch (board.at(pos))
    {
        case TL_EMPTY:      return '.';
        case TL_VERTICAL:   return '/';
        case TL_HORIZONTAL: return '\\';
        case TL_NORTH:      return 'v';
        case TL_SOUTH:      return '^';
        case TL_EAST:       return '<';
        case TL_WEST:       return '>';
    }

    throw std::logic_error("invalid tile value in char Human::GetCharAtPos(int pos)");
}

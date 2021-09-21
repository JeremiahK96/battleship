#include "global.hpp"
#include "Player.hpp"

#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <memory>

void global::DoAsserts ()
{
    AssertCoordinateInBounds();
    AssertIsValidAlphaNumeric();
}

void global::ShowSplashScreen ()
{
    std::cout
        << "Welcome to battleship, a terminal-based navy combat game.\n\n";
}

bool global::CoordinateInBounds (const unsigned int coord)
{
    return coord < board_area;
}

void global::AssertCoordinateInBounds ()
{
    assert(CoordinateInBounds(0));
    assert(!CoordinateInBounds(-1));
    assert(CoordinateInBounds(board_width * board_height - 1));
    assert(!CoordinateInBounds(board_width * board_height));
}

bool global::IsValidAlphaNumeric (const std::string &alphanum)
{
    if (alphanum.length() < 2)
        return false;

    unsigned char alpha = std::toupper(alphanum.at(0));
    unsigned char digit = alphanum.at(1);

    if (alpha < 'A' || alpha >= char('A' + board_height))
        return false;
    if (!std::isdigit(digit) || std::stoi(alphanum.substr(1)) > board_width)
        return false;

    return true;
}

void global::AssertIsValidAlphaNumeric ()
{
    std::string lo_num = "1";
    std::string hi_num = std::to_string(board_width);
    std::string lo_alp = "A";
    std::string hi_alp = "A";
    hi_alp.at(0) += board_height - 1;

    assert(!IsValidAlphaNumeric(std::string("")));
    assert(!IsValidAlphaNumeric(lo_alp));
    assert(!IsValidAlphaNumeric(hi_alp));
    assert(!IsValidAlphaNumeric(lo_num));
    assert(!IsValidAlphaNumeric(hi_num));
    assert(!IsValidAlphaNumeric(hi_alp + lo_alp));
    assert(!IsValidAlphaNumeric(lo_num + hi_alp));
    assert(!IsValidAlphaNumeric(lo_num + hi_num));
    assert(!IsValidAlphaNumeric(std::string("!*")));
    assert(!IsValidAlphaNumeric(hi_alp + "*"));
    assert(!IsValidAlphaNumeric("!" + lo_num));

    assert(IsValidAlphaNumeric(lo_alp + lo_num));
    assert(IsValidAlphaNumeric(lo_alp + hi_num));
    assert(IsValidAlphaNumeric(hi_alp + lo_num));
    assert(IsValidAlphaNumeric(hi_alp + hi_num));
}

unsigned int global::AlphaNumericToCoordinate (std::string &alphanum)
{
    assert(IsValidAlphaNumeric(alphanum));

    unsigned char alpha = std::toupper(alphanum.at(0));
    unsigned int num = std::stoi(alphanum.substr(1));

    return (alpha - 'A') * global::board_width + num - 1;
}

void global::PlayGame ()
{
    do
    {
        unsigned int num_players = QueryNumPlayers();
        assert(num_players <= 2);

        std::vector <std::unique_ptr<Player>> players;
        assert(players.empty());

        AddPlayers(players, num_players);
    } while (QueryNewGame());
}

unsigned int global::QueryNumPlayers ()
{
    unsigned int num_players = 3;

    while (num_players > 2)
    {
        std::string input;

        std::cout << "Number of players   ";
        std::getline(std::cin, input);

        if (input.size() && std::isdigit(input.at(0)))
            num_players = std::stoi(input);
    }

    return num_players;
}

void global::AddPlayers (
        std::vector <std::unique_ptr<Player>> &players,
        unsigned int num_players)
{
    // Add all Human players.
    for (int i = 0; i < num_players; ++i)
    {
        // Output 200 newlines to hide previous player's ship board setup.
        if (num_players > 1)
        {
            for (int i = 0; i < 20; ++i)
                std::cout << "\n\n\n\n\n\n\n\n\n\n";
            std::cout << "Player " << i + 1 << ' ';
        }

        std::cout << "Ship Setup:\n";

        std::unique_ptr<Human> human = std::make_unique<Human>();
        human->PlaceShips();
        players.push_back(std::move(human));
    }
    assert(players.size() == num_players);

    // Add all Computer players.
    for (int i = num_players; i < 2; ++i)
    {
        std::unique_ptr<Computer> computer = std::make_unique<Computer>();
        computer->PlaceShips();
        players.push_back(std::move(computer));
    }
    assert(players.size() == 2);
}

bool global::QueryNewGame ()
{
    std::string input;
    assert(input.empty());

    while (input.compare("y") && input.compare("n"))
    {
        std::cout << "Would you like to play again?   ";
        std::getline(std::cin, input);
    }
    assert(!input.compare("y") || !input.compare("n"));

    if (!input.compare("y"))
        return true;
    return false;
}

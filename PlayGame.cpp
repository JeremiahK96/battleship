#include "PlayGame.hpp"

#include <iostream>
#include <string>
#include <cassert>

bool PlayGame ()
{
    int players = QueryNumPlayers();

    return QueryNewGame();
}

int QueryNumPlayers ()
{
    int players = -1;

    while (players < 0 || players > 2)
    {
        std::string input;

        std::cout << "Number of players   ";
        std::getline(std::cin, input);

        if (input.size() && std::isdigit(input.at(0)))
            players = std::stoi(input);
    }
    assert(players >= 0 && players <= 2);

    return players;
}

bool QueryNewGame ()
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

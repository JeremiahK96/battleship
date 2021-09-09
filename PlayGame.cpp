#include "PlayGame.hpp"
#include "Player.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cassert>

bool PlayGame ()
{
    int num_players = QueryNumPlayers();
    assert(num_players >= 0 && num_players <= 2);

    std::vector <std::unique_ptr<Player>> players;
    assert(players.empty());

    return QueryNewGame();
}

int QueryNumPlayers ()
{
    int num_players = -1;

    while (num_players < 0 || num_players > 2)
    {
        std::string input;

        std::cout << "Number of players   ";
        std::getline(std::cin, input);

        if (input.size() && std::isdigit(input.at(0)))
            num_players = std::stoi(input);
    }

    return num_players;
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

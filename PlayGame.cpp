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

    AddPlayers(players, num_players);

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

void AddPlayers(std::vector <std::unique_ptr<Player>> &players, int num_players)
{
    // Add all Human players.
    for (int i = 0; i < num_players; ++i)
    {
        std::unique_ptr<Human> human = std::make_unique<Human>();
        human->PlaceShips();
        players.push_back(std::move(human));
    }
    assert(players.size() == num_players);

    // Add all Computer players.
    for (int i = num_players; i < 2; ++i)
    {
        std::unique_ptr<Computer> cmptr = std::make_unique<Computer>();
        players.push_back(std::move(cmptr));
    }
    assert(players.size() == 2);
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

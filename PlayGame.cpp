#include "PlayGame.hpp"

#include <iostream>
#include <string>
#include <cassert>

bool PlayGame ()
{
    return QueryNewGame();
}

bool QueryNewGame ()
{
    std::string input;
    assert(input.empty());

    while (input.compare("y") && input.compare("n"))
    {
        assert(input.compare("y") && input.compare("n"));
        std::cout << "Would you like to play again? y/n   ";
        std::getline(std::cin, input);
    }
    assert(!input.compare("y") || !input.compare("n"));

    if (!input.compare("y"))
        return true;
    return false;
}

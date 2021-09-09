#include <iostream>
#include <string>
#include <cassert>

#include "SplashScreen.hpp"

bool PlayGame ()
{
    std::string input;
    assert(input.empty());

    while (input.compare("y") && input.compare("n"))
    {
        std::cout << "Would you like to play again? y/n   ";
        std::getline(std::cin, input);
    }
    assert(!input.compare("y") || !input.compare("n"));

    if (!input.compare("y"))
        return true;
    return false;
}

int main (int argv, char **argc)
{
    SplashScreen();

    // play games until user chooses to quit
    while (PlayGame())
    {}

    return 0;
}

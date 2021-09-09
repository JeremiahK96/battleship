#include "SplashScreen.hpp"
#include "PlayGame.hpp"

int main (int argv, char **argc)
{
    SplashScreen();

    // keep playing games until user chooses to quit
    while (PlayGame())
    {}

    return 0;
}

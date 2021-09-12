#include "SplashScreen.hpp"
#include "PlayGame.hpp"
#include "global.hpp"

int main (int argv, char **argc)
{
    global::DoAsserts();

    SplashScreen();

    // Keep playing games until user chooses to quit.
    while (PlayGame())
    {}

    return 0;
}

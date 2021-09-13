#include "global.hpp"

int main (int argv, char **argc)
{
    global::DoAsserts();

    global::SplashScreen();
    global::PlayGame();

    return 0;
}

#include "global.hpp"

int main (int argv, char **argc)
{
    global::DoAsserts();

    global::ShowSplashScreen();
    global::PlayGame();

    return 0;
}

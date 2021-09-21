#pragma once

#include <vector>
#include <memory>

class Player;

namespace global
{
    inline const unsigned int board_width = 10;
    inline const unsigned int board_height = 10;
    inline const unsigned int board_area = board_height * board_width;

    inline const unsigned int ship_sizes[] = { 5, 4, 3, 3, 2 };

    void DoAsserts ();

    void ShowSplashScreen ();
    void PlayGame ();

    unsigned int QueryNumPlayers ();
    void AddPlayers(
            std::vector <std::unique_ptr<Player>> &players,
            const unsigned int num_players);
    bool QueryNewGame ();

    bool CoordinateInBounds (const unsigned int coord);
    void AssertCoordinateInBounds ();

    bool IsValidAlphaNumeric (const std::string &alphanum);
    void AssertIsValidAlphaNumeric ();
    unsigned int AlphaNumericToCoordinate (std::string &alphanum);
}

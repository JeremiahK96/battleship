#pragma once

#include <vector>
#include <memory>

#include "Player.hpp"

bool PlayGame ();
int QueryNumPlayers ();
void AddPlayers(
        std::vector <std::unique_ptr<Player>> &players,
        int num_players
        );
bool QueryNewGame ();

#include "Player.hpp"

#include <cassert>

void Player::ClearBoard ()
{
    while (!board.empty())
        board.pop_back();
    assert(board.empty());

    for (int i = 0; i < global::board_area; ++i)
        board.push_back(TL_EMPTY);
    assert(board.size() == global::board_area);
}

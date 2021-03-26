#include "player.h"
#include "util.h"
#include <iostream>
#include <algorithm>
#include <utility>

Player::Player(int window_width, int window_height, float speed)
            : Character(window_width, window_height, {{0.0, 0.8, 0.8}, {0.0, 0.7, 0.7}, {0.0, 0.65, 0.65}}, speed)
{

}

bool Player::updateActiveCell(std::pair<int, glm::vec3> new_cell)
{
    if (active_cell != new_cell)
    {
        active_cell = new_cell;
        return true;
    }
    return false;
}

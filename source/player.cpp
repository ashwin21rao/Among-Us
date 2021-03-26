#include "player.h"
#include "util.h"
#include <iostream>
#include <algorithm>
#include <utility>

Player::Player(int window_width, int window_height, float speed)
            : Character(window_width, window_height, {{0.0, 0.8, 0.8}, {0.0, 0.7, 0.7}, {0.0, 0.65, 0.65}}, speed)
{

}

void Player::translate(int key, float render_time)
{
    sprite.translate(key, render_time);
    glm::vec3 pos = sprite.getPosition();

    b_box.x = pos.x - b_box.width / 2;
    b_box.y = pos.y + b_box.height / 2;
}

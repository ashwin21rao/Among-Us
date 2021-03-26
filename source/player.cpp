#include "player.h"
#include "util.h"
#include <iostream>
#include <algorithm>

Player::Player(int window_width, int window_height, float speed)
            : sprite(window_width, window_height, speed)
{
    std::pair<std::vector<float>, int> vertex_data = generateVertexData();
    sprite.createSprite(vertex_data.first, sizeof(float) * vertex_data.first.size(), vertex_data.second);
}

std::pair<std::vector<float>, int> Player::generateVertexData()
{
    std::vector<float> vertices;
    width = 0.6, height = 0.6;
    b_box = {-width / 2, height / 2, width, height};

    int num_vertices = 0;

    generateTrianglesFromPolygon(vertices, {-0.3f, -0.3f, 0.0f,
                                            0.3f, -0.3f, 0.0f,
                                            0.3f, 0.3f, 0.0f,
                                            -0.3f, 0.3f, 0.0f}, {0.0f, 0.6f, 0.4f});
    num_vertices += 6;

    return {vertices, num_vertices};
}

void Player::translate(int key, float render_time)
{
    sprite.translate(key, render_time);
    glm::vec3 pos = sprite.getPosition();

    b_box.x = pos.x - width / 2;
    b_box.y = pos.y + height / 2;
}

void Player::moveTo(glm::vec3 position)
{
    sprite.moveTo(position);

    b_box.x = position.x - width / 2;
    b_box.y = position.y + height / 2;
}

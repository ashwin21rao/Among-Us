#include "player.h"
#include "util.h"
#include <iostream>
#include <algorithm>

Player::Player(int window_width, int window_height, float speed)
            : sprite(window_width, window_height, speed)
{
    std::pair<std::vector<float>, int> vertex_data = generateVertexData();

//    for (int i=0; i<vertex_data.first.size(); i++)
//    {
//        std::cout << vertex_data.first[i] << " ";
//        if ((i+1) % 6 == 0)
//            std::cout << std::endl;
//    }
//    std::cout << vertex_data.second << std::endl;

    sprite.createSprite(vertex_data.first, sizeof(float) * vertex_data.first.size(), vertex_data.second);
}

std::pair<std::vector<float>, int> Player::generateVertexData()
{
    std::vector<float> vertices;
    width = 0.6, height = 0.6;
    int num_vertices = 0;

    generateTrianglesFromPolygon(vertices, {-0.3f, -0.3f, 0.0f,
                                            0.3f, -0.3f, 0.0f,
                                            0.3f, 0.3f, 0.0f,
                                            -0.3f, 0.3f, 0.0f}, {0.0f, 0.6f, 0.4f});
    num_vertices += 6;

    return {vertices, num_vertices};
}

void Player::setInitialCell(std::pair<std::vector<bool>, std::pair<float, float>> cell)
{
    active_cell = cell;
    sprite.moveTo(glm::vec3(active_cell.second.first, active_cell.second.second, 0.0));
}

std::vector<int> Player::checkWallCollision(float cell_size)
{
    glm::vec3 pos = sprite.getPosition();
    float cell_x = active_cell.second.first;
    float cell_y = active_cell.second.second;

    std::vector<int> collided_walls;

    // top wall collision
    if (active_cell.first[0])
        if (pos.y + height / 2 > cell_y + cell_size / 2)
            collided_walls.push_back(0);

    // bottom wall collision
    if (active_cell.first[2])
        if (pos.y - height / 2 < cell_y - cell_size / 2)
            collided_walls.push_back(2);

    // left wall collision
    if (active_cell.first[3])
        if (pos.x - width / 2 < cell_x - cell_size / 2)
            collided_walls.push_back(3);

    // right wall collision
    if (active_cell.first[1])
        if (pos.x + width / 2 > cell_x + cell_size / 2)
            collided_walls.push_back(1);

    return collided_walls;
}

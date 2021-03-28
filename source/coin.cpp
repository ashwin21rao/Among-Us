#include "coin.h"
#include <cmath>
#include <utility>

Coin::Coin(int window_width, int window_height)
        : sprite(window_width, window_height)
{
    std::pair<std::vector<float>, int> vertex_data = generateVertexData();
    sprite.createSprite(vertex_data.first, sizeof(float) * vertex_data.first.size(), vertex_data.second);
}

std::pair<std::vector<float>, int> Coin::generateVertexData()
{
    std::vector<float> vertices;

    float r1 = 0.25, r2 = 0.15;
    b_box = {-r1 / 2, r1 / 2, 2 * r1, 2 * r1};

    int num_vertices = 0;
    num_vertices += generateCircle(r2, 0, 0, vertices, {0.93f, 0.8f, 0.14f});
    num_vertices += generateCircle(r1, 0, 0, vertices, {0.69f, 0.58f, 0.0f});

    return {vertices, num_vertices};
}

void Coin::moveTo(glm::vec3 position)
{
    sprite.moveTo(position);

    b_box.x = position.x - b_box.width / 2;
    b_box.y = position.y + b_box.height / 2;
}

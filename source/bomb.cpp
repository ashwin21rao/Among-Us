#include "bomb.h"

Bomb::Bomb(int window_width, int window_height)
        : sprite(window_width, window_height)
{
    std::pair<std::vector<float>, int> vertex_data = generateVertexData();
    sprite.createSprite(vertex_data.first, sizeof(float) * vertex_data.first.size(), vertex_data.second);
}

std::pair<std::vector<float>, int> Bomb::generateVertexData()
{
    std::vector<float> vertices;

    float r = 0.2;
    b_box = {-r / 2, r / 2, 2 * r, 2 * r};

    int num_vertices = 0;

    // circle of bomb
    num_vertices += generateCircle(r, 0, 0, vertices, {0.0, 0.0, 0.0});

    // fuse of bomb
    float w = 0.1, h = 0.3, y_offset = 0.2;
    generateTrianglesFromPolygon(vertices, {-w / 2, -h / 2 + y_offset, 0.0f,
                                            w / 2, -h / 2 + y_offset, 0.0f,
                                            w / 2, h / 2 + y_offset, 0.0f,
                                            -w / 2, h / 2 + y_offset, 0.0f}, {1.0, 0.33, 0.0});
    num_vertices += 6;

    return {vertices, num_vertices};
}

void Bomb::moveTo(glm::vec3 position)
{
    sprite.moveTo(position);

    b_box.x = position.x - b_box.width / 2;
    b_box.y = position.y + b_box.height / 2;
}

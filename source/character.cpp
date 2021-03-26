#include "character.h"
#include "util.h"
#include <iostream>
#include <algorithm>
#include <utility>

Character::Character(int window_width, int window_height, std::vector<std::vector<float>> colors, float speed)
        : sprite(window_width, window_height, speed), colors(std::move(colors))
{
    std::pair<std::vector<float>, int> vertex_data = generateVertexData();
    sprite.createSprite(vertex_data.first, sizeof(float) * vertex_data.first.size(), vertex_data.second);
}

std::pair<std::vector<float>, int> Character::generateVertexData()
{
    std::vector<float> vertices;

    float w, h, body_w, body_h, backpack_w, helmet_r;
    float top_x, top_y;
    int num_vertices = 0;
    glm::mat4 trans_mat = glm::mat4(1.0f);

    // rectangluar body
    w = 0.4, h = 0.5;
    generateTrianglesFromPolygon(vertices, {-w / 2, -h / 2, 0.0f,
                                            w / 2, -h / 2, 0.0f,
                                            w / 2, h / 2, 0.0f,
                                            -w / 2, h / 2, 0.0f}, colors[0]);
    num_vertices += 6;
    body_w = w, body_h = h;

    // backpack
    w = 0.1, h = 0.35;
    float y_offset = 0.04;
    generateTrianglesFromPolygon(vertices, {-w - body_w / 2, -h / 2 + y_offset, 0.0f,
                                            w - body_w / 2, -h / 2 + y_offset, 0.0f,
                                            w - body_w / 2, h / 2 + y_offset, 0.0f,
                                            -w - body_w / 2, h / 2 + y_offset, 0.0f}, colors[1]);
    num_vertices += 6;
    backpack_w = w;

    // visor
    w = body_w * 0.75, h = 0.15;
    generateTrianglesFromPolygon(vertices, {body_w / 2 - w, body_h / 2, 0.001f,
                                            body_w / 2, body_h / 2, 0.001f,
                                            body_w / 2, body_h / 2 - h, 0.001f,
                                            body_w / 2 - w, body_h / 2 - h, 0.001f}, colors[2]);
    num_vertices += 6;

    // semicircular head
    float r = body_w / 2;
    float x = r, y = body_h / 2;
    helmet_r = r;

    int num_points = 26;
    for (int i=1; i<=num_points / 2; i++)
    {
        float x1 = r * (float)cos(i * 2 * M_PI / num_points);
        float y1 = r * (float)sin(i * 2 * M_PI / num_points) + body_h / 2;

        generateTrianglesFromPolygon(vertices, {x, y, 0.0f,
                                                x1, y1, 0.0f,
                                                0.0f, body_h / 2, 0.0f}, colors[0]);

        x = x1, y = y1;
        num_vertices += 3;
    }

    width = body_w + backpack_w, height = body_h + helmet_r;
    b_box = {-body_w / 2 - backpack_w / 2, body_h / 2 + helmet_r / 2, width, height};

    return {vertices, num_vertices};
}

void Character::moveTo(glm::vec3 position)
{
    sprite.moveTo(position);

    b_box.x = position.x - b_box.width / 2;
    b_box.y = position.y + b_box.height / 2;
}

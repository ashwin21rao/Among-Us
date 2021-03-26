#include "button.h"
#include <cmath>
#include <utility>

Button::Button(int window_width, int window_height, std::vector<float> color)
            : sprite(window_width, window_height), color(std::move(color))
{
    std::pair<std::vector<float>, int> vertex_data = generateVertexData();
    sprite.createSprite(vertex_data.first, sizeof(float) * vertex_data.first.size(), vertex_data.second);
}

std::pair<std::vector<float>, int> Button::generateVertexData()
{
    std::vector<float> vertices;

    float radius = 0.3;
    b_box = {-radius / 2, radius / 2, 2 * radius, 2 * radius};

    int num_vertices = 0;

    float x = radius, y = 0;
    int num_points = 25;
    for (int i=1; i<=num_points; i++)
    {
        float x1 = radius * (float)cos(i * 2 * M_PI / num_points);
        float y1 = radius * (float)sin(i * 2 * M_PI / num_points);

        generateTrianglesFromPolygon(vertices, {x, y, 0.0f,
                                                x1, y1, 0.0f,
                                                0.0f, 0.0f, 0.0f}, color);

        x = x1, y = y1;
        num_vertices += 3;
    }

    return {vertices, num_vertices};
}

void Button::moveTo(glm::vec3 position)
{
    sprite.moveTo(position);

    b_box.x = position.x - b_box.width / 2;
    b_box.y = position.y + b_box.height / 2;
}

#include "button.h"

Button::Button(int window_width, int window_height)
            : sprite(window_width, window_height)
{
    color = {0.8, 0.0, 0.0};
    std::pair<std::vector<float>, int> vertex_data = generateVertexData();
    sprite.createSprite(vertex_data.first, sizeof(float) * vertex_data.first.size(), vertex_data.second);
    pressed = false;
}

std::pair<std::vector<float>, int> Button::generateVertexData()
{
    std::vector<float> vertices;

    float radius = 0.3;
    b_box = {-radius / 2, radius / 2, 2 * radius, 2 * radius};

    int num_vertices = generateCircle(radius, 0, 0, vertices, color);

    return {vertices, num_vertices};
}

void Button::moveTo(glm::vec3 position)
{
    sprite.moveTo(position);

    b_box.x = position.x - b_box.width / 2;
    b_box.y = position.y + b_box.height / 2;
}

void Button::press()
{
    pressed = true;
    color = {0.0, 0.6, 0.4};
    std::pair<std::vector<float>, int> vertex_data = generateVertexData();
    sprite.createSprite(vertex_data.first, sizeof(float) * vertex_data.first.size(), vertex_data.second);
}

bool Button::isPressed() const
{
    return pressed;
}

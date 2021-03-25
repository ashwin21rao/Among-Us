#include "player.h"
#include "util.h"
#include <iostream>

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
    int num_vertices = 0;

    generateTrianglesFromPolygon(vertices, {-0.3f, -0.3f, 0.0f,
                                            0.3f, -0.3f, 0.0f,
                                            0.3f, 0.3f, 0.0f,
                                            -0.3f, 0.3f, 0.0f}, {0.0f, 0.6f, 0.4f});
    num_vertices += 6;

    return {vertices, num_vertices};
}

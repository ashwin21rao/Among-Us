#include "game.h"
#include "window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <algorithm>

Game::Game(int window_width, int window_height) :
        player(window_width, window_height),
        maze(10, 10, window_width, window_height),
        camera(glm::vec3(0.0, 0.0, 0.0), 2),
        shader("../source/vertex_shaders/shader.vert", "../source/fragment_shaders/shader.frag")
{
    shader.use();
    sprite_list.push_back(&player.sprite);
    sprite_list.push_back(&maze.sprite);

    player.setInitialCell(maze.getRandomCell());
    camera.moveAndFocus(player.sprite.getPosition());
}

void Game::renderSprites()
{
    for (auto &sprite : sprite_list)
    {
        // load transformation matrix of sprite into shader
        sprite->setViewMatrix(camera.getViewMatrix());
        shader.transform(sprite->transformation_matrix, "trans_matrix");

        // render sprite
        sprite->render();
    }
}

void Game::movePlayer(Window &window, float render_time)
{
    bool moved = false;
//    if (glfwGetKey(window.window, GLFW_KEY_L) == GLFW_PRESS)
//        player.sprite.translate('l', render_time), moved = true;
//    else if (glfwGetKey(window.window, GLFW_KEY_J) == GLFW_PRESS)
//        player.sprite.translate('j', render_time), moved = true;
//    else if (glfwGetKey(window.window, GLFW_KEY_I) == GLFW_PRESS)
//        player.sprite.translate('i', render_time), moved = true;
//    else if (glfwGetKey(window.window, GLFW_KEY_K) == GLFW_PRESS)
//        player.sprite.translate('k', render_time), moved = true;

    std::vector<int> collided_walls = player.checkWallCollision(maze.cell_size);

    if (glfwGetKey(window.window, GLFW_KEY_L) == GLFW_PRESS)
    {
        if (find(collided_walls.begin(), collided_walls.end(), 1) == collided_walls.end())
            player.sprite.translate('l', render_time), moved = true;
    }
    else if (glfwGetKey(window.window, GLFW_KEY_J) == GLFW_PRESS)
    {
        if (find(collided_walls.begin(), collided_walls.end(), 3) == collided_walls.end())
            player.sprite.translate('j', render_time), moved = true;
    }
    else if (glfwGetKey(window.window, GLFW_KEY_I) == GLFW_PRESS)
    {
        if (find(collided_walls.begin(), collided_walls.end(), 0) == collided_walls.end())
            player.sprite.translate('i', render_time), moved = true;
    }
    else if (glfwGetKey(window.window, GLFW_KEY_K) == GLFW_PRESS)
    {
        if (find(collided_walls.begin(), collided_walls.end(), 2) == collided_walls.end())
            player.sprite.translate('k', render_time), moved = true;
    }

    if (moved)
    {
        camera.moveAndFocus(player.sprite.getPosition());
        std::cout << "Here" << std::endl;
        maze.findNextCell(player);
    }
}

//void Game::checkCollision()
//{
//
//}
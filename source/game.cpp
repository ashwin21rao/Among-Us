#include "game.h"
#include "window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <algorithm>

Game::Game(int window_width, int window_height) :
        player(window_width, window_height, 2),
        imposter(window_width, window_height, 2),
        button(window_width, window_height, {0.8, 0.0, 0.0}),
        maze(10, 10, window_width, window_height),
        camera(glm::vec3(0.0, 0.0, 0.0), 4.5),
        shader("../source/vertex_shaders/shader.vert", "../source/fragment_shaders/shader.frag")
{
    shader.use();
    sprite_list.push_back(&player.sprite);
    sprite_list.push_back(&imposter.sprite);
    sprite_list.push_back(&maze.sprite);
//    sprite_list.push_back(&button.sprite);

    player.moveTo(maze.getRandomPosition());
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
//    if (glfwGetKey(window.window, GLFW_KEY_L) == GLFW_PRESS)
//        player.sprite.translate('l', render_time), moved = true;
//    else if (glfwGetKey(window.window, GLFW_KEY_J) == GLFW_PRESS)
//        player.sprite.translate('j', render_time), moved = true;
//    else if (glfwGetKey(window.window, GLFW_KEY_I) == GLFW_PRESS)
//        player.sprite.translate('i', render_time), moved = true;
//    else if (glfwGetKey(window.window, GLFW_KEY_K) == GLFW_PRESS)
//        player.sprite.translate('k', render_time), moved = true;

//    std::vector<int> collided_walls = player.checkWallCollision(maze.cell_size);
//
//    if (glfwGetKey(window.window, GLFW_KEY_L) == GLFW_PRESS)
//    {
//        if (find(collided_walls.begin(), collided_walls.end(), 1) == collided_walls.end())
//            player.sprite.translate('l', render_time), moved = true;
//    }
//    else if (glfwGetKey(window.window, GLFW_KEY_J) == GLFW_PRESS)
//    {
//        if (find(collided_walls.begin(), collided_walls.end(), 3) == collided_walls.end())
//            player.sprite.translate('j', render_time), moved = true;
//    }
//    else if (glfwGetKey(window.window, GLFW_KEY_I) == GLFW_PRESS)
//    {
//        if (find(collided_walls.begin(), collided_walls.end(), 0) == collided_walls.end())
//            player.sprite.translate('i', render_time), moved = true;
//    }
//    else if (glfwGetKey(window.window, GLFW_KEY_K) == GLFW_PRESS)
//    {
//        if (find(collided_walls.begin(), collided_walls.end(), 2) == collided_walls.end())
//            player.sprite.translate('k', render_time), moved = true;
//    }

    bool collided = false;
    bool moved = false;

    if (glfwGetKey(window.window, GLFW_KEY_L) == GLFW_PRESS)
    {
        for (auto &wall : maze.walls)
        {
            if (checkLeftCollision(wall, player.b_box))
            {
                collided = true;
                break;
            }
        }
        if (!collided)
            player.translate('l', render_time), moved = true;
    }
    else if (glfwGetKey(window.window, GLFW_KEY_J) == GLFW_PRESS)
    {
        for (auto &wall : maze.walls)
        {
            if (checkRightCollision(wall, player.b_box))
            {
                collided = true;
                break;
            }
        }
        if (!collided)
            player.translate('j', render_time), moved = true;
    }
    else if (glfwGetKey(window.window, GLFW_KEY_I) == GLFW_PRESS)
    {
        for (auto &wall : maze.walls)
        {
            if (checkBottomCollision(wall, player.b_box))
            {
                collided = true;
                break;
            }
        }
        if (!collided)
            player.translate('i', render_time), moved = true;
    }
    else if (glfwGetKey(window.window, GLFW_KEY_K) == GLFW_PRESS)
    {
        for (auto &wall : maze.walls)
        {
            if (checkTopCollision(wall, player.b_box))
            {
                collided = true;
                break;
            }
        }
        if (!collided)
            player.translate('k', render_time), moved = true;
    }

    if (moved)
        camera.moveAndFocus(player.sprite.getPosition());
}

// b2 with left of b1
bool Game::checkLeftCollision(bounding_box &b1, bounding_box &b2) const
{
    return (abs(b2.x + b2.width - b1.x) <= collision_threshold) && (b2.y - b2.height <= b1.y && b2.y >= b1.y - b1.height);
}

// b2 with right of b1
bool Game::checkRightCollision(bounding_box &b1, bounding_box &b2) const
{
    return (abs(b2.x - (b1.x + b1.width)) <= collision_threshold) && (b2.y - b2.height <= b1.y && b2.y >= b1.y - b1.height);
}

// b2 with top of b1
bool Game::checkTopCollision(bounding_box &b1, bounding_box &b2) const
{
    return (abs(b2.y - b2.height - b1.y) <= collision_threshold) && (b2.x + b2.width >= b1.x && b2.x <= b1.x + b1.width);
}

// b2 with bottom of b1
bool Game::checkBottomCollision(bounding_box &b1, bounding_box &b2) const
{
    return (abs(b2.y - (b1.y - b1.height)) <= collision_threshold) && (b2.x + b2.width >= b1.x && b2.x <= b1.x + b1.width);
}

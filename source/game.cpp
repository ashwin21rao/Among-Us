#include "game.h"
#include "window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/epsilon.hpp>
#include <iostream>
#include <algorithm>

Game::Game(int window_width, int window_height) :
        player(window_width, window_height, 2),
        imposter(window_width, window_height, 2),
        button(window_width, window_height, {0.8, 0.0, 0.0}),
        maze(10, 10, window_width, window_height),
        camera(glm::vec3(0.0, 0.0, 0.0), 20),
        shader("../source/vertex_shaders/shader.vert", "../source/fragment_shaders/shader.frag")
{
    shader.use();
    sprite_list.push_back(&player.sprite);
    sprite_list.push_back(&imposter.sprite);
    sprite_list.push_back(&maze.sprite);
//    sprite_list.push_back(&button.sprite);

    player.setInitialPosition(maze.getRandomCell());
    imposter.setInitialPosition(maze.getRandomCell());
    imposter.updatePath(maze.findShortestPath(imposter.active_cell.first, player.active_cell.first));

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

void Game::moveSprites(Window &window, float render_time)
{
    movePlayer(window, render_time);
    moveImposter(render_time);
}

void Game::moveImposter(float render_time)
{
    imposter.move(maze.width, render_time);

    glm::vec3 pos = imposter.sprite.getPosition();

    // if imposter moves to position of next cell
    glm::vec3 p = glm::epsilonEqual(imposter.sprite.getPosition(), imposter.next_cell.second, glm::vec3(0.05));
//    std::cout << p.x << " " << p.y << std::endl;

    if (p.x && p.y)
    {
//        std::cout << "Hereeee" << std::endl;
//        std::cout << imposter.active_cell.second.x << " " << imposter.active_cell.second.y << std::endl;
//        std::cout << imposter.next_cell.second.x << " " << imposter.next_cell.second.y << std::endl;
        imposter.updateActiveCell(imposter.next_cell);
    }
//    imposter.updateActiveCell(maze.findNextCell(imposter.active_cell, imposter.sprite.getPosition()));

    // if active cell of imposter changes, update path position

    // find next cell of imposter
//    maze.findShortestPath(imposter.active_cell, player.active_cell);
}

void Game::movePlayer(Window &window, float render_time)
{
    bool collided = false;
    char direction = 0;

    bool (Game::*collision_function)(bounding_box &, bounding_box &) const;
    collision_function = &Game::checkLeftCollision;

    if (glfwGetKey(window.window, GLFW_KEY_L) == GLFW_PRESS)
    {
        collision_function = &Game::checkLeftCollision;
        direction = 'r';
    }
    else if (glfwGetKey(window.window, GLFW_KEY_J) == GLFW_PRESS)
    {
        collision_function = &Game::checkRightCollision;
        direction = 'l';
    }
    else if (glfwGetKey(window.window, GLFW_KEY_I) == GLFW_PRESS)
    {
        collision_function = &Game::checkBottomCollision;
        direction = 'u';
    }
    else if (glfwGetKey(window.window, GLFW_KEY_K) == GLFW_PRESS)
    {
        collision_function = &Game::checkTopCollision;
        direction = 'd';
    }

    if (direction == 'r' || direction == 'l' || direction == 'u' || direction == 'd')
    {
        for (auto &wall : maze.walls)
        {
            if ((this->*collision_function)(wall, player.b_box))
            {
                collided = true;
                break;
            }
        }
        if (!collided)
        {
            player.translate(direction, render_time);
            glm::vec3 pos = player.sprite.getPosition();

            // if player active cell changes, update imposter path
            if (player.updateActiveCell(maze.findNextCell(player.active_cell, pos)))
                imposter.updatePath(maze.findShortestPath(imposter.active_cell.first, player.active_cell.first));

            camera.moveAndFocus(pos);
        }
    }
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

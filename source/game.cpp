#include "game.h"
#include "window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/epsilon.hpp>
#include <iostream>
#include <algorithm>

Game::Game(int window_width, int window_height) :
        player(window_width, window_height, 3),
        imposter(window_width, window_height, 2),
        maze(10, 10, window_width, window_height),
        camera(glm::vec3(0.0, 0.0, 0.0), 4),
        shader("../source/vertex_shaders/light_shader.vert", "../source/fragment_shaders/light_shader.frag"),
        th(window_width, window_height),
        window_width(window_width), window_height(window_height),
        number_of_coins(5), number_of_bombs(5),
        start_time(glfwGetTime()), total_time(60)
{
    // initialize buttons
    buttons = {Button(window_width, window_height), Button(window_width, window_height)};
    buttons[0].moveTo(maze.getRandomPosition());
    buttons[1].moveTo(maze.getRandomPosition());

    // initialize player
    player.setInitialPosition(maze.getRandomCell());
    camera.moveAndFocus(player.sprite.getPosition());

    // initialize imposter
    imposter.setInitialPosition(maze.getRandomCell());
    imposter.updatePath(maze.findShortestPath(imposter.active_cell.first, player.active_cell.first));
}

bool Game::gameOver() const
{
    return game_over;
}

bool Game::gameWon() const
{
    return game_won;
}

void Game::tick()
{
    time_elapsed = glfwGetTime() - start_time;
    if (time_elapsed > total_time)
        game_over = true;
}

void Game::renderSprites()
{
    std::vector<Sprite*> sprite_list = {&maze.sprite, &player.sprite};
    if (imposter.isAlive())
        sprite_list.push_back(&imposter.sprite);

    for (auto &button : buttons)
        sprite_list.push_back(&button.sprite);
    for (auto &coin : coins)
        sprite_list.push_back(&coin.sprite);
    for (auto &bomb : bombs)
        sprite_list.push_back(&bomb.sprite);

    glm::vec3 pos = player.sprite.getPosition();

    shader.use();
    shader.setVec3(glm::vec3(1.0f, 1.0f, 1.0f), "lightColor");
    shader.setVec3(glm::vec3(pos.x, pos.y, 0.5), "lightPos");
    shader.setVec3(pos, "viewPos");

    for (auto &sprite : sprite_list)
    {
        // load transformation matrix of sprite into shader
        sprite->setViewMatrix(camera.getViewMatrix());
        shader.setMat4(sprite->projection_matrix, "projection");
        shader.setMat4(sprite->view_matrix, "view");
        shader.setMat4(sprite->model_matrix, "model");
//        shader.setMat4(sprite->transformation_matrix, "trans_matrix");

        // render sprite
        sprite->render();
    }

    displayText();
}

void Game::displayText()
{
    th.renderText("Score: " + std::to_string(score), 5, (float)window_height - 25, 0.5, glm::vec3(0.0, 0.0, 0.0));
    th.renderText("Time remaining: " + std::to_string((int)(total_time - time_elapsed)),
                  5, (float)window_height - 50, 0.5, glm::vec3(0.0, 0.0, 0.0));
    th.renderText("Tasks left: " + std::to_string(!buttons[0].isPressed() + !buttons[1].isPressed()),
                  5, (float)window_height - 75, 0.5, glm::vec3(0.0, 0.0, 0.0));
    th.renderText("Central lighting: On", 5, (float)window_height - 100, 0.5, glm::vec3(0.0, 0.0, 0.0));
}

void Game::moveSprites(Window &window, float render_time)
{
    movePlayer(window, render_time);

    if (imposter.isAlive())
        moveImposter(render_time);
}

void Game::moveImposter(float render_time)
{
    imposter.move(maze.width, render_time);

    glm::vec3 pos = imposter.sprite.getPosition();

    glm::vec3 p = glm::epsilonEqual(imposter.sprite.getPosition(), imposter.next_cell.second, glm::vec3(0.05));
    if (p.x && p.y)
        imposter.updateActiveCell(imposter.next_cell);
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
            {
                if (imposter.isAlive())
                    imposter.updatePath(maze.findShortestPath(imposter.active_cell.first, player.active_cell.first));
            }

            if (player.active_cell.first == maze.exit_cell.first)
            {
                glm::vec3 p = glm::epsilonEqual(player.sprite.getPosition(), maze.exit_cell.second, glm::vec3(0.3));
                if (p.x && p.y)
                    game_won = true;
            }

            camera.moveAndFocus(pos);
        }
    }
}

void Game::handleCollisions()
{
    if (imposter.isAlive() && checkCollision(player.b_box, imposter.b_box))
    {
        game_over = true;
        return;
    }

    if (!buttons[0].isPressed() && checkCollision(buttons[0].b_box, player.b_box))
    {
        buttons[0].press();
        imposter.kill();

        if (buttons[1].isPressed())
            maze.openExit();
    }
    else if (!buttons[1].isPressed() && checkCollision(buttons[1].b_box, player.b_box))
    {
        buttons[1].press();
        for (int i=0; i<number_of_coins; i++)
        {
            Coin coin(window_width, window_height);
            coin.moveTo(maze.getRandomPosition());
            coins.push_back(std::move(coin));
        }
        for (int i=0; i<number_of_bombs; i++)
        {
            Bomb bomb(window_width, window_height);
            bomb.moveTo(maze.getRandomPosition());
            bombs.push_back(std::move(bomb));
        }

        if (buttons[0].isPressed())
            maze.openExit();
    }
    else
    {
        // check coin collision
        for (auto it=coins.begin(); it!=coins.end(); it++)
        {
            if (checkCollision(it->b_box, player.b_box))
            {
                score += 10;
                coins.erase(it);
                return;
            }
        }

        // check bomb collision
        for (auto it=bombs.begin(); it!=bombs.end(); it++)
        {
            if (checkCollision(it->b_box, player.b_box))
            {
                score -= 10;
                bombs.erase(it);
                return;
            }
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

// any collision (overlap of bounding boxes)
bool Game::checkCollision(bounding_box& b1, bounding_box& b2)
{
    return (b2.y - b2.height <= b1.y && b2.y >= b1.y - b1.height) && (b2.x + b2.width >= b1.x && b2.x <= b1.x + b1.width);
}

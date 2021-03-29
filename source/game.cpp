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
        maze(15, 15, window_width, window_height),
        camera(glm::vec3(0.0, 0.0, 0.0), 15),
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
    imposter.updatePath(maze.findShortestPath(imposter.active_cell.first, player.active_cell.first), maze.width);

    // initialize shaders
    shaders = {Shader("../source/vertex_shaders/shader.vert", "../source/fragment_shaders/shader.frag"),
               Shader("../source/vertex_shaders/light_shader.vert", "../source/fragment_shaders/light_shader.frag")};

    shaders[1].use();
    shaders[1].setVec3(glm::vec3(0.1f, 0.1f, 0.1f), "light.ambient");
    shaders[1].setVec3(glm::vec3(1.0f, 1.0f, 1.0f), "light.diffuse");
    shaders[1].setVec3(glm::vec3(1.0f, 1.0f, 1.0f), "light.specular");

    shaders[1].setVec3(glm::vec3(0.0f, 0.0f, -1.0f), "light.direction");
    shaders[1].setFloat(glm::cos(glm::radians(25.0f)), "light.cutOff");
    shaders[1].setFloat(glm::cos(glm::radians(45.0f)), "light.outerCutOff");

    shaders[1].setFloat(1.0f, "light.constant");
    shaders[1].setFloat(0.09f, "light.linear");
    shaders[1].setFloat(0.032f, "light.quadratic");
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

void Game::processInput(Window &window)
{
    static bool space_pressed = false;
    if (!space_pressed && glfwGetKey(window.window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        lights_off = !lights_off;
        if (lights_off)
        {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

            glm::vec3 pos = player.sprite.getPosition();
            shaders[1].use();
            shaders[1].setVec3(glm::vec3(pos.x, pos.y, 1.0), "light.position");
            shaders[1].setVec3(pos, "viewPos");
        }
        else
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        space_pressed = true;
    }
    else if (space_pressed && glfwGetKey(window.window, GLFW_KEY_SPACE) == GLFW_RELEASE)
        space_pressed = false;
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

    Shader current_shader = lights_off ? shaders[1] : shaders[0];
    current_shader.use();

    for (auto &sprite : sprite_list)
    {
        // load transformation matrix of sprite into shader
        sprite->setViewMatrix(camera.getViewMatrix());

        if (lights_off)
            current_shader.setMat4(sprite->model_matrix, "model_matrix");
        current_shader.setMat4(sprite->transformation_matrix, "trans_matrix");

        // render sprite
        sprite->render();
    }

    displayText();
}

void Game::displayText()
{
    glm::vec3 color = (lights_off) ? glm::vec3(1.0) : glm::vec3(0.0);

    th.renderText("Score: " + std::to_string(score), 5, (float)window_height - 25, 0.5, color);
    th.renderText("Time remaining: " + std::to_string((int)(total_time - time_elapsed)),
                  5, (float)window_height - 50, 0.5, color);
    th.renderText("Tasks left: " + std::to_string(!buttons[0].isPressed() + !buttons[1].isPressed()),
                  5, (float)window_height - 75, 0.5, color);
    th.renderText("Central lighting: " + std::string(lights_off ? "Off" : "On"),
                  5, (float)window_height - 100, 0.5, color);
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
                    imposter.updatePath(maze.findShortestPath(imposter.active_cell.first, player.active_cell.first), maze.width);
            }

            if (player.active_cell.first == maze.exit_cell.first)
            {
                glm::vec3 p = glm::epsilonEqual(player.sprite.getPosition(), maze.exit_cell.second, glm::vec3(0.3));
                if (p.x && p.y)
                    game_won = true;
            }

            camera.moveAndFocus(pos);

            // update position of light
            if (lights_off)
            {
                shaders[1].use();
                shaders[1].setVec3(glm::vec3(pos.x, pos.y, 1.0), "light.position");
                shaders[1].setVec3(pos, "viewPos");
            }
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
                score += lights_off ? 20 : 10;
                coins.erase(it);
                return;
            }
        }

        // check bomb collision
        for (auto it=bombs.begin(); it!=bombs.end(); it++)
        {
            if (checkCollision(it->b_box, player.b_box))
            {
                score -= lights_off ? 5 : 10;
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

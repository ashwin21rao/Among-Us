#include "game.h"
#include "window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Game::Game(int window_width, int window_height) :
        player(window_width, window_height),
        maze(10, 10, window_width, window_height),
        camera(glm::vec3(0.0, 0.0, 0.0), 2),
        shader("../source/vertex_shaders/shader.vert", "../source/fragment_shaders/shader.frag")
{
    shader.use();
    sprite_list.push_back(&player.sprite);
    sprite_list.push_back(&maze.sprite);

    player.sprite.moveTo(maze.getStartPosition());
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
    if (glfwGetKey(window.window, GLFW_KEY_L) == GLFW_PRESS)
        player.sprite.translate('l', render_time), moved = true;
    else if (glfwGetKey(window.window, GLFW_KEY_J) == GLFW_PRESS)
        player.sprite.translate('j', render_time), moved = true;
    else if (glfwGetKey(window.window, GLFW_KEY_I) == GLFW_PRESS)
        player.sprite.translate('i', render_time), moved = true;
    else if (glfwGetKey(window.window, GLFW_KEY_K) == GLFW_PRESS)
        player.sprite.translate('k', render_time), moved = true;

    if (moved)
        camera.moveAndFocus(player.sprite.getPosition());
}

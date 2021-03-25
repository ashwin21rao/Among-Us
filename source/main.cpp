#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "window.h"
#include "shader.h"
#include "shape.h"
#include "camera.h"
#include "maze.h"
#include "sprite.h"
#include "movable_sprite.h"
#include "player.h"
#include "game.h"
#include <vector>
#include <iostream>

// create window
Window window(1200, 800);

// sprite list
std::vector<Sprite*> sprite_list;

void translateCamera(int key, Sprite &sprite, Camera &camera, Shader &shader, float render_time)
{
    camera.translate(key, render_time);
    sprite.setViewMatrix(camera.getViewMatrix());
    shader.transform(sprite.transformation_matrix, "trans_matrix");
}

void processInput(Game &game, float render_time)
{
    // general commands
    if (glfwGetKey(window.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window.window, true);

    // translate player
    game.movePlayer(window, render_time);

//    if (glfwGetKey(window.window, GLFW_KEY_L) == GLFW_PRESS)
//        game.player.sprite.translate('l', render_time);
//    else if (glfwGetKey(window.window, GLFW_KEY_J) == GLFW_PRESS)
//        game.player.sprite.translate('j', render_time);
//    else if (glfwGetKey(window.window, GLFW_KEY_I) == GLFW_PRESS)
//        game.player.sprite.translate('i', render_time);
//    else if (glfwGetKey(window.window, GLFW_KEY_K) == GLFW_PRESS)
//        game.player.sprite.translate('k', render_time);

//    // translate camera
//    if (glfwGetKey(window.window, GLFW_KEY_D) == GLFW_PRESS)
//        translateCamera('d', sprite, camera, shader, render_time);
//    else if (glfwGetKey(window.window, GLFW_KEY_A) == GLFW_PRESS)
//        translateCamera('a', sprite, camera, shader, render_time);
//    else if (glfwGetKey(window.window, GLFW_KEY_W) == GLFW_PRESS)
//        translateCamera('w', sprite, camera, shader, render_time);
//    else if (glfwGetKey(window.window, GLFW_KEY_S) == GLFW_PRESS)
//        translateCamera('s', sprite, camera, shader, render_time);
//    else if (glfwGetKey(window.window, GLFW_KEY_Q) == GLFW_PRESS)
//        translateCamera('q', sprite, camera, shader, render_time);
//    else if (glfwGetKey(window.window, GLFW_KEY_E) == GLFW_PRESS)
//        translateCamera('e', sprite, camera, shader, render_time);
}

int main()
{
    // initialize window
    window.initialize();

    // enable depth testing
    glEnable(GL_DEPTH_TEST);

    // set background color
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // create game object
    Game game(window.width, window.height);

    // create and use shader program
//    Shader shader("../source/vertex_shaders/shader.vert", "../source/fragment_shaders/shader.frag");
//    shader.use();

    // create camera
//    Camera camera(glm::vec3(0.0, 0.0, 0.0), 2);

    // initialize maze
//    Maze maze(10, 10);
//    camera.moveAndFocus(maze.getStartPosition());
//    maze.sprite.setViewMatrix(camera.getViewMatrix());
//    shader.transform(maze.sprite.transformation_matrix, "trans_matrix");

    // create player
//    Player player(window.width, window.height);

    // to keep track of time taken for each render
    float last_frame_timestamp = 0.0, current_frame_timestamp;

    // render loop
    while (!glfwWindowShouldClose(window.window))
    {
        current_frame_timestamp = (float)glfwGetTime();

        // check for events
        processInput(game, current_frame_timestamp - last_frame_timestamp);

        // rendering commands
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render shapes
//        shape.render();
        game.renderSprites();
//        maze.render();

        // update display
        glfwSwapBuffers(window.window);
        glfwPollEvents();
        last_frame_timestamp = current_frame_timestamp;
    }

    glfwDestroyWindow(window.window);
    glfwTerminate();

    return 0;
}

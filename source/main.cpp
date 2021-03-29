#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "window.h"
#include "game.h"
#include <ft2build.h>
#include FT_FREETYPE_H

void processInput(Window &window)
{
    if (glfwGetKey(window.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window.window, true);
}

int main()
{
    // initialize window
    Window window(1200, 800);
    window.initialize();

    // enable opengl options
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // set background color
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

    // create game object
    Game game(window.width, window.height);

    // to keep track of time taken for each render
    float last_frame_timestamp = 0.0, current_frame_timestamp;

    // render loop
    while (!glfwWindowShouldClose(window.window))
    {
//        if (game.gameOver() || game.gameWon())
//            break;

        current_frame_timestamp = (float)glfwGetTime();

        // check for window events
        processInput(window);

        // process game input
        game.processInput(window);

        // move sprites
        game.moveSprites(window, current_frame_timestamp - last_frame_timestamp);

        // check for collisions
        game.handleCollisions();

        // render sprites
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        game.renderSprites();

        // tick game timer
        game.tick();

        // update display
        glfwSwapBuffers(window.window);
        glfwPollEvents();
        last_frame_timestamp = current_frame_timestamp;
    }

    glfwDestroyWindow(window.window);
    glfwTerminate();

    return 0;
}

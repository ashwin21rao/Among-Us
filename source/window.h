#ifndef _WINDOW_H
#define _WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    Window(int window_width, int window_height);
    bool initialize();
    GLFWwindow *window;
    int width, height;
private:
    static void errorCallback(int error, const char *description);
    static void windowResizeCallback(GLFWwindow *window, int width, int height);
};


#endif

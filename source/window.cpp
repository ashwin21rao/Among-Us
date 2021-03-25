#include "window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdio>

Window::Window(int window_width, int window_height)
        : width(window_width), height(window_height), window(nullptr)
{

}

bool Window::initialize()
{
    int glfwInitRes = glfwInit();
    if (!glfwInitRes)
    {
        fprintf(stderr, "Unable to initialize GLFW\n");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width, height, "InitGL", nullptr, nullptr);
    if (!window)
    {
        fprintf(stderr, "Unable to create GLFW window\n");
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);

    int gladInitRes = gladLoadGL();
    if (!gladInitRes)
    {
        fprintf(stderr, "Unable to initialize glad\n");
        glfwDestroyWindow(window);
        glfwTerminate();
        return false;
    }

    glViewport(0, 0, width, height);

    glfwSetErrorCallback(errorCallback);
    glfwSetFramebufferSizeCallback(window, windowResizeCallback);

    return true;
}

void Window::errorCallback(int error, const char *description)
{
    fprintf(stderr, "GLFW error %d: %s\n", error, description);
}

void Window::windowResizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

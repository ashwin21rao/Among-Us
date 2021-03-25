#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdio>
#include "shader.h"

using namespace glm;

namespace
{
    void errorCallback(int error, const char *description)
    {
        fprintf(stderr, "GLFW error %d: %s\n", error, description);
    }

    void windowResizeCallback(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    GLFWwindow *initialize()
    {
        int glfwInitRes = glfwInit();
        if (!glfwInitRes)
        {
            fprintf(stderr, "Unable to initialize GLFW\n");
            return nullptr;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        int window_width = 800, window_height = 600;
        GLFWwindow *window = glfwCreateWindow(window_width, window_height, "InitGL", nullptr, nullptr);
        if (!window)
        {
            fprintf(stderr, "Unable to create GLFW window\n");
            glfwTerminate();
            return nullptr;
        }

        glfwMakeContextCurrent(window);

        int gladInitRes = gladLoadGL();
        if (!gladInitRes)
        {
            fprintf(stderr, "Unable to initialize glad\n");
            glfwDestroyWindow(window);
            glfwTerminate();
            return nullptr;
        }

        glViewport(0, 0, window_width, window_height);
        return window;
    }
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
}

unsigned int createShape()
{
    // vertex data
    float vertices[] = {
            // positions          // colors
            -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f
    };

    // index data
    unsigned int indices[] = {
            0, 1, 3,  // first triangle
            1, 2, 3   // second triangle
    };

    // create and use a vertex array object (VAO)
    // which stores the VBO, EBO and mapping of vertex data to attributes for that object
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // create and use a vertex buffer object (VBO) to load vertices into GPU memory
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // create and use an element buffer object (EBO) to load indices into GPU memory
    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // specify mapping of vertex data to vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    return vao;
}

int main()
{
    glfwSetErrorCallback(errorCallback);

    // create window
    GLFWwindow *window = initialize();
    if (!window)
        return 0;

    glfwSetFramebufferSizeCallback(window, windowResizeCallback);

    // enable depth testing
    glEnable(GL_DEPTH_TEST);

    // set the clear color to a nice green
    glClearColor(0.15f, 0.6f, 0.4f, 1.0f);

    // create shader program
    Shader shader("../source/vertex_shaders/shader.vert", "../source/fragment_shaders/shader.frag");

    // create triangle VAO
    unsigned int vao = createShape();

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // check for events
        processInput(window);

        // rendering commands
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // use shader program
        shader.use();

        // transform local -> world -> view -> clip coordinates
        mat4 model_matrix = mat4(1.0f);
        model_matrix = rotate(model_matrix, (float)glfwGetTime(), vec3(0.5, 1.0, 0.0));

        mat4 view_matrix = mat4(1.0f);
        view_matrix = translate(view_matrix, vec3(0.0, 0.0, -3.0));

        mat4 projection_matrix = mat4(1.0f);
        projection_matrix = perspective((float)radians(45.0f), float(800)/600, 0.1f, 100.0f);

        mat4 transform_matrix = projection_matrix * view_matrix * model_matrix;
        shader.transform(transform_matrix, "trans_matrix");
//        glUniformMatrix4fv(glGetUniformLocation(shader.shader_id, "trans_matrix"), 1, GL_FALSE, value_ptr(transform_matrix));

        // render shape
        glBindVertexArray(vao);        // bind VAO of object
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)nullptr);  // draw vertices (elements)
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // update display
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

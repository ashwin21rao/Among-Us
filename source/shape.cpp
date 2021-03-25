#include "shape.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "iostream"

Shape::Shape(int window_width, int window_height)
            : x_speed(2.0), y_speed(2.0), z_speed(2.0), rotation_speed(1.5),
              translation_matrix(glm::mat4(1.0f)), rotation_matrix(glm::mat4(1.0f)), scaling_matrix(glm::mat4(1.0f))
{
    model_matrix = translation_matrix * rotation_matrix * scaling_matrix;
    view_matrix = glm::translate(view_matrix, glm::vec3(0.0, 0.0, -5.0));
    projection_matrix = glm::perspective((float)glm::radians(45.0f), (float)window_width / (float)window_height, 0.1f, 100.0f);
    calculateMatrices();
}

void Shape::createShape(float *vertices, int size, int number_of_vertices, float scaling_factor)
{
    num_vertices = number_of_vertices;

    if (scaling_factor != 1)
    {
        scaling_matrix = glm::scale(scaling_matrix, glm::vec3(scaling_factor));
        calculateMatrices();
    }

    // create and use a vertex array object (VAO)
    // which stores the VBO, EBO and mapping of vertex data to attributes for that object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // create and use a vertex buffer object (VBO) to load vertices into GPU memory
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    // specify mapping of vertex data to vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
}

void Shape::render() const
{
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, num_vertices);
}

void Shape::translate(int key, float render_time)
{
    glm::vec3 translation_vector(0.0f);

    if(key == 'l')
        translation_vector = glm::vec3(x_speed * render_time, 0.0, 0.0);
    else if(key == 'j')
        translation_vector = glm::vec3(-x_speed * render_time, 0.0, 0.0);
    else if(key == 'i')
        translation_vector = glm::vec3(0.0, y_speed * render_time, 0.0);
    else if(key == 'k')
        translation_vector = glm::vec3(0.0, -y_speed * render_time, 0.0);
    else if(key == 'u')
        translation_vector = glm::vec3(0.0, 0.0, z_speed * render_time);
    else if(key == 'o')
        translation_vector = glm::vec3(0.0, 0.0, -z_speed * render_time);

    translation_matrix = glm::translate(translation_matrix, translation_vector);
    calculateMatrices();
}

void Shape::rotate(glm::vec3 axis, float render_time)
{
    rotation_matrix = glm::rotate(rotation_matrix, rotation_speed * render_time, axis);
    calculateMatrices();
}

void Shape::calculateMatrices()
{
    model_matrix = translation_matrix * rotation_matrix * scaling_matrix;
    transformation_matrix = projection_matrix * view_matrix * model_matrix;
}

void Shape::setViewMatrix(glm::mat4 new_view_matrix)
{
    view_matrix = new_view_matrix;
    calculateMatrices();
}

glm::vec3 Shape::getCenter() const
{
    glm::vec4 center = model_matrix * glm::vec4(0.0, 0.0, 0.0, 1.0);
    return glm::vec3(center);
}

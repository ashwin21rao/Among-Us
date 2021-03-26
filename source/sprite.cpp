#include "sprite.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Sprite::Sprite(int window_width, int window_height)
        : translation_matrix(glm::mat4(1.0f)), rotation_matrix(glm::mat4(1.0f)), scaling_matrix(glm::mat4(1.0f))
{
    initial_position = glm::vec3(0.0);

    model_matrix = translation_matrix * rotation_matrix * scaling_matrix;
    view_matrix = glm::mat4(1.0f);
    projection_matrix = glm::perspective((float) glm::radians(45.0f), (float) window_width/(float) window_height, 0.1f,
                                         100.0f);
//    projection_matrix = glm::ortho(0.0f, (float)window_width, (float)window_height, 0.0f, -1.0f, 1.0f);
    calculateMatrices();
}

void Sprite::createSprite(const std::vector<float> &vertex_data, int size, int number_of_vertices)
{
    vertices = vertex_data;
    num_vertices = number_of_vertices;

    // create and use a vertex array object (VAO)
    // which stores the VBO, EBO and mapping of vertex data to attributes for that object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // create and use a vertex buffer object (VBO) to load vertices into GPU memory
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, vertices.data(), GL_STATIC_DRAW);

    // specify mapping of vertex data to vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void *) nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void *) (3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
}

void Sprite::render() const
{
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, num_vertices);
}

void Sprite::calculateMatrices()
{
    model_matrix = translation_matrix * rotation_matrix * scaling_matrix;
    transformation_matrix = projection_matrix * view_matrix * model_matrix;
}

void Sprite::setViewMatrix(glm::mat4 new_view_matrix)
{
    view_matrix = new_view_matrix;
    calculateMatrices();
}

void Sprite::moveTo(glm::vec3 position)
{
    translation_matrix = glm::mat4(1.0f);
    translation_matrix = glm::translate(translation_matrix, position - initial_position);
    calculateMatrices();
}

glm::vec3 Sprite::getPosition() const
{
    return glm::vec3(translation_matrix * glm::vec4(initial_position, 1.0));
}

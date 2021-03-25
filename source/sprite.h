#ifndef _SPRITE_H
#define _SPRITE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>


class Sprite
{
public:
    Sprite(int window_width, int window_height);
    void createSprite(const std::vector<float> &vertices, int size, int number_of_vertices);
    void render() const;
    void setViewMatrix(glm::mat4 new_view_matrix);
    void moveTo(glm::vec3 position);
    glm::vec3 getPosition() const;

    glm::vec3 initial_position;

    // transformation matrices
    glm::mat4 model_matrix, view_matrix, projection_matrix, transformation_matrix;
    glm::mat4 translation_matrix, rotation_matrix, scaling_matrix;

protected:
    void calculateMatrices();
    unsigned int vao;
    std::vector<float> vertices;
    int num_vertices;
};


#endif
